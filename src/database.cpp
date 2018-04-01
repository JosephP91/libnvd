#include "../include/database.hpp"

#include <iostream>

#include <mongocxx/instance.hpp>


void nvd::database::init() {
    mongocxx::instance driver_instance{};
}

auto nvd::database::execute(nvd::operation::base_write &operation) {
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

void nvd::database::index(operation::index &operation) {
    auto indexes = operation.get_data();
    for (auto &index: indexes) {
        this->collection.create_index(index.first, index.second);
    }
}

void nvd::database::drop_collection() {
    this->collection.drop();
}