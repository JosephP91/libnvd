#ifndef NVD_FILE_LOADER_HPP
#define NVD_FILE_LOADER_HPP

#include <string>

#include "json.hpp"

using std::string;
using std::ifstream;

using nlohmann::json;

namespace nvd {
    class file_loader {
    public:
        static json load(const string &);
        static json load(const char *);
    };
}


#endif //NVD_FILE_LOADER_HPP
