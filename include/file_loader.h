#ifndef MIMPORT_STREAM_LOADER_H
#define MIMPORT_STREAM_LOADER_H

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


#endif //MIMPORT_STREAM_LOADER_H
