#include <iostream>
#include <cstdlib>

#include "file.hpp"
#include "operation.hpp"
#include "client.hpp"

using std::cerr;
using std::endl;
using std::exit;


int main(int argc, char **argv) {
    // Check arguments number.
    if (argc < 2) {
        cerr << "Usage: ./updater.out nvd_archive.json" << endl;
        exit(EXIT_FAILURE);
    }

    // Load the configuration file and the archive to process.
    json config = nvd::file::load("../config.json");
    json archive = nvd::file::load(argv[1]);

    // Client settings and client instantiation.
    nvd::client::settings settings(config["database"], config["collection"]);
    nvd::client client(settings);

    // Create the update data operation and execute it.
    nvd::operation::update update_operation(archive);
    client.execute(update_operation);

    exit(EXIT_SUCCESS);
}
