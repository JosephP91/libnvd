#include <iostream>
#include <cstdlib>

#include "file.hpp"
#include "database.hpp"

using std::exit;


int main(int argc, char **argv) {
    // Load the configuration file.
    json config_file = nvd::file::load("../config.json");

    // Load the nvd database.
    nvd::database database(config_file["database"], config_file["collection"]);
    // Index the collection.
    database.build_indexes(config_file["indexes"]);

    exit(EXIT_SUCCESS);
}
