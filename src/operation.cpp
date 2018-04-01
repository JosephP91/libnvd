#include <string>

#include "../include/operation.hpp"

using std::string;


void nvd::operation::write::append(const mongocxx::model::write &operation) {
    this->operations.append(operation);
}

mongocxx::bulk_write nvd::operation::write::get_data() {
    return std::move(this->operations);
}

nvd::operation::insert::insert(const nlohmann::json &file) {
    for (const auto &item: file.at("CVE_Items")) {
        // Create the document from the JSON item.
        bsoncxx::document::value document = std::move(bsoncxx::from_json(item.dump()));

        // Create the insert operation.
        mongocxx::model::insert_one insert_operation {
            document.view()
        };

        // Append the operation that must be executed.
        this->append(insert_operation);
    }
}

nvd::operation::update::update(const nlohmann::json &file) {
    for (const auto &item: file.at("CVE_Items")) {
        // Build the search document criteria.
        bsoncxx::builder::stream::document filter_builder;
        filter_builder << "cve.CVE_data_meta.ID" << item["cve"]["CVE_data_meta"]["ID"].get<string>();

        // Build the updated document.
        bsoncxx::builder::stream::document update_builder;
        update_builder << "$set" << bsoncxx::from_json(item.dump());

        // Create the update operation using those documents.
        mongocxx::model::update_one upsert_operation {
            filter_builder.view(),
            update_builder.view()
        };
        upsert_operation.upsert(true);

        // Append the operation that must be executed.
        this->append(upsert_operation);
    }
}

nvd::operation::index::index(const nlohmann::json &indexes) {
    for (const auto &index: indexes) {
        // Check index options.
        mongocxx::options::index index_options{};
        auto unique = index["unique"].get<bool>();
        if (unique) {
            index_options.unique(true);
        }

        // Create the index document with the name and the type specified in the config file.
        auto index_document = bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp(
                index["name"].get<string>(),
                index["type"].get<int>()
        ));

        // Insert the index into the indexes map.
        this->indexes.push_back(std::make_pair(
                std::move(index_document),
                std::move(index_options)
        ));
    }
}

nvd::operation::index::indexes_vector_type nvd::operation::index::get_data() {
    return std::move(this->indexes);
}

