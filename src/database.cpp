#include "../include/database.hpp"

#include <iostream>
#include <vector>

#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

using std::vector;

void nvd::database::init() {
    mongocxx::instance driver_instance{};
}

nvd::database::database(const string &name, const string &collection) {
    std::call_once(mongo_once_init_flag, &nvd::database::init, this);
    this->client = mongocxx::uri{};
    this->collection = this->client[name][collection];
}

int32_t nvd::database::import(const json &file) {
    // Create a vector of documents to rapidly store the documents.
    vector<bsoncxx::document::value> documents;
    for (const auto &item: file.at("CVE_Items")) {
        auto document = bsoncxx::from_json(item.dump());
        documents.push_back(document);
    }

    // Insert options. Disable ordering and document validation.
    mongocxx::options::insert options;
    options.bypass_document_validation(true);
    options.ordered(false);

    // Perform the bulk insert.
    auto result = this->collection.insert_many(documents,options);

    // Return the number of stored documents.
    return result.value().inserted_count();
}

int32_t nvd::database::update(const json &file) {
    // Create a set of write operations.
    mongocxx::bulk_write bulk_operations{};

    for (const auto &item: file.at("CVE_Items")) {
        // Build the search document.
        bsoncxx::builder::stream::document filter_builder;
        filter_builder << "cve.CVE_data_meta.ID"
                       << item["cve"]["CVE_data_meta"]["ID"].get<string>();

        // Build the update document.
        bsoncxx::builder::stream::document update_builder;
        update_builder << "$set" << bsoncxx::from_json(item.dump());

        // Create the update operation using those documents.
        mongocxx::model::update_one upsert_operation{
                filter_builder.view(),
                update_builder.view()
        };
        upsert_operation.upsert(true);

        // Append the operation that must be executed.
        bulk_operations.append(upsert_operation);
    }

    // Execute the bulk write and returns the upserted number of records.
    auto result = this->collection.bulk_write(bulk_operations);
    return result.value().upserted_count();
}

void nvd::database::build_indexes(const json &indexes) {
    for (const auto &index: indexes) {
        mongocxx::options::index index_options{};

        // Check index options.
        string name = index["name"].get<string>();
        auto type = index["type"].get<int>();
        auto unique = index["unique"].get<bool>();

        if (unique) {
            index_options.unique(true);
        }

        // Create the index.
        bsoncxx::builder::stream::document index_builder;
        index_builder << name << type;
        this->collection.create_index(index_builder.view(), index_options);
    }
}

void nvd::database::drop_collection() {
    this->collection.drop();
}