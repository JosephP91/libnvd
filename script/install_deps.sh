#!/usr/bin/env bash

# Exit on error.
set -e

# Check machine.
uname_machine="$(uname -s)"
case "${uname_machine}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    *)          machine="Unsupported machine:${uname_machine}. Exiting" exit;;
esac

# If we are on Linux, install mongodb and ensure all packages are installed.
if [ "$machine" == "Linux" ] ;then
    sudo apt-get update && sudo apt-get -y install cmake g++ pkg-config mongodb lynx unzip tar
fi

# Install latest mongoc driver
wget https://github.com/mongodb/mongo-c-driver/releases/download/1.9.3/mongo-c-driver-1.9.3.tar.gz
tar -zxf mongo-c-driver-1.9.3.tar.gz
rm ./mongo-c-driver-1.9.3.tar.gz
cd mongo-c-driver-1.9.3

# Beginning in OS X 10.11 El Capitan, OS X no longer includes the OpenSSL headers. This fixes it.
if [ "$machine" == "Mac" ] ;then
    export LDFLAGS="-L/usr/local/opt/openssl/lib"
    export CPPFLAGS="-I/usr/local/opt/openssl/include"
fi

./configure --disable-automatic-init-and-cleanup
make
sudo make install
cd ../
sudo rm -rf ./mongo-c-driver-1.9.3

# Install last stable release of mongocxx driver
git clone https://github.com/mongodb/mongo-cxx-driver.git --branch releases/stable --depth 1
cd mongo-cxx-driver/build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local ..
sudo make EP_mnmlstc_core
make
sudo make install
cd ../../
sudo rm -rf ./mongo-cxx-driver

exit 0
