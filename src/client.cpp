#include "client.hpp"

#include <mongocxx/instance.hpp>


void nvd::client::init() {
    mongocxx::instance driver_instance{};
}

auto nvd::client::_execute(nvd::operation::base_write &operation) {
    return this->collection.bulk_write(operation.get_data());
}

nvd::client::client(const nvd::client::settings &settings) {
    std::call_once(mongo_once_init_flag, &nvd::client::init, this);
    mongocxx::client client = mongocxx::uri{settings.get_uri()};
    this->collection = client[settings.get_database()][settings.get_collection()];
}

int32_t nvd::client::execute(operation::insert &operation) {
    auto result = this->_execute(operation);
    return result.value().inserted_count();
}

int32_t nvd::client::execute(operation::update &operation) {
    auto result = this->_execute(operation);
    return result.value().upserted_count();
}

void nvd::client::execute(operation::index &operation) {
    auto indexes = operation.get_data();
    for (auto &index: indexes) {
        this->collection.create_index(index.first, index.second);
    }
}

void nvd::client::drop_collection() {
    this->collection.drop();
}

nvd::client::settings::settings(const string &db, const string &coll) noexcept {
    this->database = db;
    this->collection = coll;
    this->uri = mongocxx::uri::k_default_uri;
}

nvd::client::settings::settings(const string &db, const string &coll, const bsoncxx::string::view_or_value &uri) noexcept {
    this->database = db;
    this->collection = coll;
    this->uri = uri;
}

string nvd::client::settings::get_database() const noexcept {
    return this->database;
}

string nvd::client::settings::get_collection() const noexcept {
    return this->collection;
}

bsoncxx::string::view_or_value nvd::client::settings::get_uri() const noexcept {
    return this->uri;
}