#ifndef NVD_DATABASE_HPP
#define NVD_DATABASE_HPP

#include <string>

#include <mongocxx/client.hpp>

#include "json.hpp"

using std::string;
using nlohmann::json;

namespace nvd {
    class database {
    public:
        explicit database(const string &, const string &);
        int32_t import(const json &);
        int32_t update(const json &);
        void build_indexes(const json &);
        void drop_collection();
    private:
        mongocxx::client client;
        mongocxx::collection collection;
    };
}

#endif //NVD_DATABASE_HPP