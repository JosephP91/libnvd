#!/usr/bin/env bash

# Exit on error
set -e

# apt-key for mongodb 3.2
sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv EA312927
echo "deb http://repo.mongodb.org/apt/ubuntu xenial/mongodb-org/3.2 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-3.2.list

# Install various packages.
sudo apt-get update
sudo apt-get -y install cmake g++ pkg-config mongodb-org php-mongodb

# Install mongoc driver (1.8.2 because it's the recommended version for mongodb 3.2)
wget https://github.com/mongodb/mongo-c-driver/releases/download/1.8.2/mongo-c-driver-1.8.2.tar.gz
tar -zxf mongo-c-driver-1.8.2.tar.gz
rm ./mongo-c-driver-1.8.2.tar.gz
cd mongo-c-driver-1.8.2
./configure --disable-automatic-init-and-cleanup
make
sudo make install
cd ../
rm -rf ./mongo-c-driver-1.8.2

# Install last stable release of mongocxx driver
git clone https://github.com/mongodb/mongo-cxx-driver.git --branch releases/stable --depth 1
cd mongo-cxx-driver/build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local ..
sudo make EP_mnmlstc_core
make
sudo make install
cd ../../
rm -rf ./mongo-cxx-driver

exit 0