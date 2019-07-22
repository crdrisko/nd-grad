#!/bin/bash
# Name: linkBashful.sh - (Listing 12-9)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/22/2019-08:27:27
# Description: Make multiple links to bashful script

cd "$HOME/bin" &&
for name in sleepy sneezy grumpy dopey
do
    ln -s bashful "$name"           ## you can leave out the -s option if you like
dones
