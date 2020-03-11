#!/bin/bash
# Copyright (c) 2020 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for license information.
#
# Name: install-cpp-units.sh - Version 1.0.0
# Author: cdrisko
# Date: 03/09/2020-12:24:20
# Description: Install cpp-units prior to install

mkdir ~/CPP-Units && cd ~/CPP-Units

git clone https://github.com/crdrisko/cpp-units.git

bash cpp-units/ci/install-utilities-api.sh

mkdir build && cd build

cmake ../cpp-units/.

make && sudo make install

cd ../
