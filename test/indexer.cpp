#include <iostream>
#include <cstdlib>

#include <mongocxx/instance.hpp>

#include "../include/file_loader.hpp"
#include "../include/database.hpp"

using std::exit;


int main(int argc, char **argv) {
    // Load the configuration file.
    json config_file = nvd::file_loader::load("../config.json");

    // Load MongoDB driver instance.
    mongocxx::instance driver_instance{};
    // Load the nvd database.
    nvd::database database = nvd::database(config_file["database"], config_file["collection"]);
    // Index the collection.
    database.build_indexes(config_file["indexes"]);

    exit(EXIT_SUCCESS);
}
