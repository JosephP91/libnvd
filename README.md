# nvd-import
nvd-import is a command line utility written in C++ using libmongoc, libbson , mongo C++ driver (mongocxx driver) and a 
JSON parser, to store, index and update in a MongoDB database the National Vulnerabilities Database locally.

# Dependencies
The software depends on ```libmongoc```, ```libbson``` and ```mongo-cxx-driver```. These dependencies will be automatically installed
executing the installation script, located under the script directory:

```bash
cd script
./install.sh
```

If you're using Linux, eveything will be installed using the script. Instead, if you are using Mac OS, 
you have to install the following packaged: ```cmake g++ pkg-config mongodb-org php-mongodb lynx unzip```. 
You can use brew to handle this installation.

# Compile
Now that you have all the dependencies installed, you can compile the sources doing this:

```bash
cd script
./compile.sh
```

The executables will be placed under the ```out``` directory.

# The configuration file

You can use the configuration file, config.json, to change the database and the collection name to use. Plus, you can add more mongodb indexes to speed up the query. If you want to know which fields you can index, take a look at the files content listed here: https://nvd.nist.gov/vuln/data-feeds#JSON_FEED

# Importing the national vulnerability database
In oreder to create a database with the national vulnerabilities, you have to download the JSON files from 
https://nvd.nist.gov/vuln/data-feeds#JSON_FEED. You will find a JSON file for every year until now, plus two
files which contains the modified and recent vulerabilities, that you can use to sync your local database with 
the new discovered vulnerabilities. You can use the download script placed under the script directory. It will
download every JSON feed on the page in the ```feed``` directory.

I recommend you to separate the modified and recent JSON feed, from the yearly feed files.
You can place these files wherever you want, for example:

```bash
# Store yearly JSON feed here.
cd nvd-import
mkdir -p ./feeds/insert

# Store modified and recent files here.
mkdir -p ./feeds/update
```

Then you can start to import those files using the script nvd_import.sh:

```bash
cd script
./import.sh path_to_yearly_json_feed
```

Wait until the all the files are processed. Then, you can process the recent and modified files:

```bash
cd script
./update.sh path_to_recent_and_modified_files
```

Done! :)


