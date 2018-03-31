#include "../include/database.hpp"

#include <iostream>

#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/document.hpp>


void nvd::database::init() {
    mongocxx::instance driver_instance{};
}

auto nvd::database::execute(nvd::operation::base &operation) {
    return this->collection.bulk_write(operation.get_data());
}

nvd::database::database(const string &name, const string &collection) {
    // mongodb istance will be initialized just once, even in a multithreading envinronment.
    std::call_once(mongo_once_init_flag, &nvd::database::init, this);
    this->client = mongocxx::uri{};
    this->collection = this->client[name][collection];
}

int32_t nvd::database::import(operation::insert &operation) {
    auto result = this->execute(operation);
    return result.value().inserted_count();
}

int32_t nvd::database::update(operation::update &operation) {
    auto result = this->execute(operation);
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