#!/usr/bin/env bash

##############################################################
# USE THIS SCRIPT TO COMPILE SOURCES UNDER THE SRC DIRECTORY #
##############################################################

# Exit on error.
set -e

# Check if ouput directory exists.
if [ ! -d "../out" ]; then
    mkdir ../out
fi

# Move to sources folder.
cd ../src

# Compile the importer.
printf "Compiling importer ... "
g++ -std=c++11 importer.cpp database.cpp file_loader.cpp -o ../out/importer.out $(pkg-config --cflags --libs libmongocxx) -Wall -pedantic -Wl,-rpath,/usr/local/lib
printf "Done.\n"

# Compile the indexer.
printf "Compiling indexer ... "
g++ -std=c++11 indexer.cpp database.cpp file_loader.cpp -o ../out/indexer.out $(pkg-config --cflags --libs libmongocxx) -Wall -pedantic -Wl,-rpath,/usr/local/lib
printf "Done.\n"

# Compile the updater.
printf "Compiling updater ... "
g++ -std=c++11 updater.cpp database.cpp file_loader.cpp -o ../out/updater.out $(pkg-config --cflags --libs libmongocxx) -Wall -pedantic -Wl,-rpath,/usr/local/lib
printf "Done\n"

# Compile the dropper.
printf "Compiling dropper ... "
g++ -std=c++11 dropper.cpp database.cpp file_loader.cpp -o ../out/dropper.out $(pkg-config --cflags --libs libmongocxx) -Wall -pedantic -Wl,-rpath,/usr/local/lib
printf "Done\n"