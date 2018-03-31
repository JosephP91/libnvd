#include "file.hpp"

#include <fstream>

using std::ifstream;


json nvd::file::load(const std::string &file) {
    ifstream file_stream(file);
    if (file_stream.fail()) {
        throw std::invalid_argument("File " + file + " does not exists!");
    }
    return json::parse(file_stream);
}


json nvd::file::load(const char *file) {
    string file_string(file);
    return nvd::file::load(file_string);
}