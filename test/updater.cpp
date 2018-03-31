#include <iostream>
#include <cstdlib>

#include "file_loader.hpp"
#include "database.hpp"

using std::cerr;
using std::endl;
using std::exit;


int main(int argc, char **argv) {
    // Check arguments number.
    if (argc < 2) {
        cerr << "Usage: ./updater.out nvd_archive.json" << endl;
        exit(EXIT_FAILURE);
    }

    // Load the archive file to process.
    json archive_file = nvd::file_loader::load(argv[1]);
    // Load the configuration file.
    json config_file = nvd::file_loader::load("../config.json");

    // Load the nvd database.
    nvd::database database(config_file["database"], config_file["collection"]);
    // Update the database.
    database.update(archive_file);

    exit(EXIT_SUCCESS);
}
