#ifndef NVD_DATABASE_HPP
#define NVD_DATABASE_HPP

#include <string>
#include <mutex>

#include <mongocxx/client.hpp>

#include "json.hpp"

using std::string;
using nlohmann::json;

namespace nvd {
    class database {
    private:
        mongocxx::client client;
        mongocxx::collection collection;
        std::once_flag mongo_once_init_flag;
        void init();
    public:
        explicit database(const string &, const string &);

        database(const database &) = delete;
        database& operator=(const database &) = delete;
        database& operator=(database &&) = delete;

        int32_t import(const json &);
        int32_t update(const json &);
        void build_indexes(const json &);
        void drop_collection();
    };
}

#endif //NVD_DATABASE_HPP