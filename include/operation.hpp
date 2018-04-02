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
            base() = default;
            base(base &) noexcept = delete;
            base(base &&) noexcept = default;
            base& operator=(base&&) noexcept = delete;
            virtual ~base() = default;

            virtual T get_data();
        };

        /**
         * Base class of the write operations, so operations that will insert/update/delete
         * records in the database.
         */
        class base_write : public base<mongocxx::bulk_write> {
        public:
            base_write() = default;
            base_write(base_write &) noexcept = delete;
            base_write(base_write &&) noexcept = default;
            base_write& operator=(base_write&&) noexcept = delete;
            ~base_write() override = default;
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
            insert(insert &) noexcept = delete;
            insert(insert &&) noexcept = default;
            insert& operator=(insert&&) noexcept = delete;
            ~insert() override = default;
        };

        /**
         * Update operation class. It reads a JSON file and create documents that must be updated/insereted
         * in the database.
         */
        class update : public base_write {
        public:
            explicit update(const nlohmann::json &);
            update(update &) noexcept = delete;
            update(update &&) noexcept = default;
            update& operator=(update&&) noexcept = delete;
            ~update() override = default;
        };

        /**
         * Index operation class. The constructor takes a JSON array containing the indexes, and their options,
         * that must be created on the desired collection.
         */
        class index : public base<indexes_vector_type> {
        public:
            explicit index(const nlohmann::json &);
            index(index &) noexcept = delete;
            index(index &&) noexcept = default;
            index& operator=(index&&) noexcept = delete;
            ~index() override = default;
        };
    }
}

#endif //NVD_OPERATION_HPP
