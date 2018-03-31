#include <string>

#include "../include/operation.hpp"

using std::string;


void nvd::operation::base::append(const mongocxx::model::write &operation) {
    this->operations.append(operation);
}

mongocxx::bulk_write nvd::operation::base::get_data() {
    mongocxx::bulk_write ops(std::move(this->operations));
    return ops;
}

nvd::operation::insert::insert(const nlohmann::json &file) {
    for (const auto &item: file.at("CVE_Items")) {
        bsoncxx::document::value document = bsoncxx::from_json(item.dump());
        mongocxx::model::insert_one insert_operation { document.view() };
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

