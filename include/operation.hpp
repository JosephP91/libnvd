#ifndef NVD_OPERATION_HPP
#define NVD_OPERATION_HPP

#include <vector>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>

#include "../include/json.hpp"

namespace nvd {
    namespace operation  {

        class write {
        private:
            mongocxx::bulk_write operations;
        protected:
            void append(const mongocxx::model::write &);
        public:
            mongocxx::bulk_write get_data();
        };

        class insert : public write {
        public:
            explicit insert(const nlohmann::json &);
        };

        class update : public write {
        public:
            explicit update(const nlohmann::json &);
        };

        class index {
            using indexes_vector_type = std::vector<
                    std::pair<bsoncxx::document::view_or_value , mongocxx::options::index> >;
        private:
            indexes_vector_type indexes;
        public:
            explicit index(const nlohmann::json &);
            indexes_vector_type get_data();
        };
    }
}

#endif //NVD_OPERATION_HPP
