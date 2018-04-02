#include <iostream>
#include <cstdlib>

#include "file.hpp"
#include "operation.hpp"
#include "database.hpp"

using std::cerr;
using std::endl;
using std::exit;


int main(int argc, char **argv) {
    // Check arguments number.
    if (argc < 2) {
        cerr << "Usage: ./importer.out nvd_archive.json" << endl;
        exit(EXIT_FAILURE);
    }

    // Load the configuration file.
    json config_file = nvd::file::load("../config.json");
    // Load the archive file to process.
    json archive_file = nvd::file::load(argv[1]);

    // Create the insert data operation.
    nvd::operation::insert insert_operation(archive_file);

    // Load the nvd database.
    nvd::database database(config_file["database"], config_file["collection"]);
    // Execute the import operation.
    database.import(insert_operation);

    exit(EXIT_SUCCESS);
}
