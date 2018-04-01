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
        // Let's shrink this big ass type.
        using indexes_vector_type = std::vector<std::pair<bsoncxx::document::view_or_value, mongocxx::options::index>>;

        /**
         * Base operation class. It has a generic structure which all the derived class
         * can use to store the operation that must be applied on the database.
         *
         * @tparam
         */
        template<class T> class base {
        protected:
            T data;
        public:
            virtual T get_data();
            virtual ~base() = default;
        };

        /**
         * Base class of the write operations, so operations that will insert/update/delete
         * records in the database.
         */
        class base_write : public base<mongocxx::bulk_write> {
        protected:
            void append(const mongocxx::model::write &);
        };

        /**
         * Insert operation class. It reads a JSON file and create documents that must be stored
         * in the database.
         */
        class insert : public base_write {
        public:
            explicit insert(const nlohmann::json &);
            ~insert() override = default;
        };

        /**
         * Update operation class. It reads a JSON file and create documents that must be updated/insereted
         * in the database.
         */
        class update : public base_write {
        public:
            explicit update(const nlohmann::json &);
            ~update() override = default;
        };

        /**
         * Index operation class. The constructor takes a JSON array containing the indexes, and their options,
         * that must be created on the desired collection.
         */
        class index : public base<indexes_vector_type> {
        public:
            explicit index(const nlohmann::json &);
            ~index() override = default;
        };
    }
}

#endif //NVD_OPERATION_HPP
