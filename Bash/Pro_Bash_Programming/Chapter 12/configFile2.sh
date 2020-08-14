#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
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
