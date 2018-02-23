#include "../include/file_loader.h"

#include <fstream>

using std::ifstream;


json nvd::file_loader::load(const std::string &file) {
    ifstream file_stream(file);
    if (file_stream.fail()) {
        throw std::invalid_argument("File " + file + " does not exists!");
    }
    return json::parse(file_stream);
}


json nvd::file_loader::load(const char *file) {
    string file_string(file);
    return nvd::file_loader::load(file_string);
}