#!/bin/bash

rm -rf thirdparty
mkdir thirdparty
cd thirdparty

wget https://sourceforge.net/projects/boost/files/boost/1.66.0/boost_1_66_0.tar.gz
if [[ $? != 0 ]]; then
  echo "ERROR: failed to install boost 1.66";
  exit 1;
fi
tar -xvf boost_1_66_0.tar.gz
rm boost_1_66_0.tar.gz

git clone https://github.com/nlohmann/json.git
git clone https://github.com/nlohmann/fifo_map.git
