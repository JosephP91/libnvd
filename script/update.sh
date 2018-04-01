#!/usr/bin/env bash

##############################################
# USE THIS SCRIPT TO UPDATE THE NDV ARCHIVES #
##############################################

# Exit on error.
set -e

# Check arguments number.
if [ $# -lt 1 ] ;then
    printf "Usage: update.sh update_archive_path\n"
    exit 1
fi

# Process every JSON in the archive directory specified.
for file in $(ls $1 | grep ".json")
do
    printf "Parsing and storing/updating ${file} ... "
    ../test/updater.out $1/${file}
    printf "Done.\n"
done

exit 0
