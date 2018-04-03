#include <iostream>
#include <cstdlib>

#include "file.hpp"
#include "client.hpp"
#include "operation.hpp"

using std::exit;


int main(int argc, char **argv) {
    // Load the configuration file.
    json config = nvd::file::load("../config.json");

    // Client settings and istantiation of the client
    nvd::client::settings settings(config["database"], config["collection"]);
    nvd::client client(settings);

    // Create the index operation and execute it.
    nvd::operation::index index_operation(config["indexes"]);
    client.execute(index_operation);

    exit(EXIT_SUCCESS);
}
