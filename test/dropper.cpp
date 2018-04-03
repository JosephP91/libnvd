#include <iostream>
#include <cstdlib>

#include "file.hpp"
#include "client.hpp"

using std::exit;


int main(int argc, char **argv) {
    // Load the configuration file.
    json config = nvd::file::load("../config.json");

    // Client settings and istantiation of the client
    nvd::client::settings settings(config["database"], config["collection"]);
    nvd::client client(settings);

    // Drop the collection.
    client.drop_collection();

    exit(EXIT_SUCCESS);
}
