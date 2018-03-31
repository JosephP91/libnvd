#ifndef NVD_OPERATION_HPP
#define NVD_OPERATION_HPP

#include <vector>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include "../include/json.hpp"

namespace nvd {
    namespace operation  {

        class base {
        private:
            mongocxx::bulk_write operations;
        protected:
            void append(const mongocxx::model::write &);
        public:
            mongocxx::bulk_write get_data();
        };

        class insert : public base {
        public:
            explicit insert(const nlohmann::json &);
        };

        class update : public base {
        public:
            explicit update(const nlohmann::json &);
        };
    }
}

#endif //NVD_OPERATION_HPP
