#!/bin/bash
# Name: configFile2.sh - (Listing 12-7)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/22/2019-08:17:58
# Description: Parsing configuration file (words.cfg) with comments

while read assignment x comment
do
    if [ -n "$assignment" ]
    then
        printf "%20s: %s\n" "${assignment#*=}" "$comment"
        eval "$assignment"
    fi
done < "$file"
