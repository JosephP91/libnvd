#include <iostream>
#include <cstdlib>

#include <mongocxx/instance.hpp>

#include "../include/file_loader.h"
#include "../include/database.hpp"

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

    // Load MongoDB driver instance
    mongocxx::instance driver_instance{};
    // Load the nvd database.
    nvd::database database = nvd::database(config_file["database"], config_file["collection"]);
    // Update the database.
    database.update(archive_file);

    exit(EXIT_SUCCESS);
}
