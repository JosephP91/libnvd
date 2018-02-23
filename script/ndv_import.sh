#!/usr/bin/env bash

##############################################
# USE THIS SCRIPT TO IMPORT THE NDV ARCHIVES #
##############################################

# Exit on error.
set -e

# Check arguments number.
if [ $# -lt 1 ] ;then
    printf "Usage: ndv_import.sh insert_archive_path\n"
    exit 1
fi

# Drop the collection if already exists.
printf "Dropping the nvd collection ... "
../out/dropper.out
printf "Done.\n"

# Process every JSON in the archive directory specified.
for file in $(ls $1 | grep ".json")
do
    printf "Parsing and storing ${file} ... "
    ../out/importer.out $1/${file}
    printf "Done.\n"
done

# Build index to improve query speed.
printf "Building index ... "
../out/indexer.out
printf "Done.\n"

exit 0
