#ifndef NVD_DATABASE_HPP
#define NVD_DATABASE_HPP

#include <string>
#include <mutex>

#include <mongocxx/client.hpp>

#include "../include/operation.hpp"

using std::string;

namespace nvd {
    /**
     * This class represents the client that will execute the operations.
     * It initializes the mongodb istance and handles the collection.
     */
    class client {
    private:
        /**
         * The collection where the archives will be stored.
         */
        mongocxx::collection collection;
        /**
         * This flag allows to initialize mongodb istance only once, even in a
         * multithreading environment.
         */
        std::once_flag mongo_once_init_flag;
        /**
         * This method initializes the mongodb istance.
         */
        void init();
        /**
         * Utility that executes a write operation on the specified collection.
         * @return the bulk_write result.
         */
        auto _execute(operation::base_write &);
    public:

        /**
         * This class handles the database settings. Users can specify the database name
         * and the collection in which store or update the nvd informations.
         */
        class settings {
        private:
            /**
             * Tha database name.
             */
            string database;
            /*+
             * The collection name.
             */
            string collection;
            /**
             * A MongoDB connection uri.
             */
            bsoncxx::string::view_or_value uri;
        public:
            /**
             * Constructor with parameters. Allows to initialize the settings using a
             * database name, collection name and default MongoDB connection uri.
             */
            explicit settings(const string &, const string &) noexcept;
            /**
             * Overloaded constructor. Allows to initialize the settings using a database
             * name, collection name and a MongoDB connection uri.
             */
            explicit settings(const string &, const string &, const bsoncxx::string::view_or_value &) noexcept;
            /**
             * This method returns the database name specified.
             * @return the database name.
             */
            string get_database() const noexcept;
            /**
             * This method returns the database collection name specified.
             * @return the collection name.
             */
            string get_collection() const noexcept;
            /**
             * This method returns the MongoDB connection uri.
             * @return the MongoDB connection uri
             */
            bsoncxx::string::view_or_value get_uri() const noexcept;
        };

        /**
         * The constructor allows to initialize the client using the settings specified as parameter.
         */
        explicit client(const nvd::client::settings &);
        /**
         * Copy constructor, copy assignment operator, move constructor, move assignment operator are deleted.
         * I don't see why a client should be copied or moved, also because there are certain class data members
         * that cannot be copied/moved.
         */
        client(const client &) = delete;
        client& operator=(const client &) = delete;
        client(client &&) = delete;
        client& operator=(client &&) = delete;

        /**
         * Default destructor.
         */
        ~client() noexcept = default;

        /**
         * This method executes an insert operation.
         * @return the result of the insert operation.
         */
        int32_t execute(operation::insert &);
        /**
         * This method executes an update operation.
         * @return the result of the update operation.
         */
        int32_t execute(operation::update &);
        /*
         * This method executes an indexing operation.
         */
        void execute(operation::index &);
        /**
         * This metho drops the collection specified before.
         */
        void drop_collection();
    };
}

#endif //NVD_DATABASE_HPP