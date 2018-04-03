#ifndef NVD_FILE_LOADER_HPP
#define NVD_FILE_LOADER_HPP

#include <string>

#include "json.hpp"

using std::string;
using std::ifstream;

using nlohmann::json;

namespace nvd {
    /**
     * This class allows to load a JSON file.
     */
    class file {
    public:
        /**
         * These two methods allows to load a JSON file.
         * @return the JSON content.
         */
        static json load(const string &);
        static json load(const char *);
    };
}

#endif //NVD_FILE_LOADER_HPP
