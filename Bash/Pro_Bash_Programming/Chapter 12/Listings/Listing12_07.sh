#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing12_07.sh - Version 1.0.0
# Author: crdrisko
# Date: 07/22/2019-08:17:58
# Description: Parsing configuration file (Listing12_05.cfg) with comments

while read assignment x comment
do
    if [ -n "$assignment" ]
    then
        printf "%20s: %s\n" "${assignment#*=}" "$comment"
        eval "$assignment"
    fi
done < "$file"
