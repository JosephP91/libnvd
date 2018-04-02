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

If you need to customize the install script, you can easly edit it.

# Install
You can compile the project and install the library doing this:

```bash
cd build
cmake ..
make
sudo make install
```

# Compile
Now that you have all the dependencies installed, you can compile the test sources typing the following commands. The library uses some facilities of C++14 standard, so be sure your compiler supports it.

```bash
cd script
./compile.sh
```

# The configuration file

You can use the configuration file, config.json, to change the database and the collection name to use. Plus, you can add more mongodb indexes to speed up the query. If you want to know which fields you can index, take a look at the files content listed here: https://nvd.nist.gov/vuln/data-feeds#JSON_FEED

# Importing the national vulnerability database
In oreder to create a database with the national vulnerabilities, you have to download the JSON files from 
https://nvd.nist.gov/vuln/data-feeds#JSON_FEED. You will find a JSON file for every year until now, plus two
files which contains the modified and recent vulerabilities, that you can use to sync your local database with 
the new discovered vulnerabilities. You can use the download script placed under the script directory. It will
download every JSON feed on the page in the ```feed``` directory.

```bash
# Download all the JSON files
cd nvd-import/script
./download
```

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


