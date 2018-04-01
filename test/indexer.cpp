#include <iostream>
#include <cstdlib>

#include "file.hpp"
#include "database.hpp"
#include "operation.hpp"

using std::exit;


int main(int argc, char **argv) {
    // Load the configuration file.
    json config_file = nvd::file::load("../config.json");

    // Create the index operation.
    nvd::operation::index index_operation(config_file["indexes"]);
    // Load the nvd database.
    nvd::database database(config_file["database"], config_file["collection"]);
    // Index the collection.
    database.index(index_operation);

    exit(EXIT_SUCCESS);
}
