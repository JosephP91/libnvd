#!/usr/bin/env bash

# Download path
path="../feeds"
output_feed="feeds.html"

# Exit on error.
set -e

# Download the HTML page of the feeds.
wget -O ${output_feed} https://nvd.nist.gov/vuln/data-feeds#JSON_FEED

# Process the HTML feeds extracting the URLS to the JSON feed.
urls=($(lynx -dump -listonly ./${output_feed} | grep .json.zip | awk '{print $2}'))

# Delete
rm ./feeds.html

# Calculate length of the vector.
urls_length=$(echo ${#urls[@]})

# Check if the feeds directory does not exsits.
if [ ! -d "$path" ]; then
    mkdir ${path}
fi

# Download every feed in the feeds directory and extract it.
for (( i=0; i<urls_length; ++i ));
do
    wget --directory-prefix=${path} ${urls[i]}
    filename=$(basename ${urls[i]})
    full_path="${path}/${filename}"
    unzip ${full_path} -d ${path}
    rm -f ${full_path}
done

exit
