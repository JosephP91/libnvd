#!/usr/bin/env bash

##############################################################
# USE THIS SCRIPT TO COMPILE SOURCES UNDER THE SRC DIRECTORY #
##############################################################

# Exit on error.
set -e

# Move to sources folder.
cd ../test

# Compile the importer.
printf "Compiling importer ... "
g++ -std=c++14 importer.cpp -o importer.out -lnvd $(pkg-config --cflags --libs libmongocxx) -Wall -pedantic -Wl,-rpath,/usr/local/lib
printf "Done.\n"

# Compile the indexer.
printf "Compiling indexer ... "
g++ -std=c++14 indexer.cpp -o indexer.out -lnvd $(pkg-config --cflags --libs libmongocxx) -Wall -pedantic -Wl,-rpath,/usr/local/lib
printf "Done.\n"

# Compile the updater.
printf "Compiling updater ... "
g++ -std=c++14 updater.cpp -o updater.out -lnvd $(pkg-config --cflags --libs libmongocxx) -Wall -pedantic -Wl,-rpath,/usr/local/lib
printf "Done\n"

# Compile the dropper.
printf "Compiling dropper ... "
g++ -std=c++14 dropper.cpp -o dropper.out -lnvd $(pkg-config --cflags --libs libmongocxx) -Wall -pedantic -Wl,-rpath,/usr/local/lib
printf "Done\n"