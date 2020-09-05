#!/bin/bash
# Copyright (c) 2019 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: Exercise3_02.sh - Version 1.0.0
# Author: crdrisko
# Date: 06/29/2019-13:58:42
# Description: Checks the existence of a file inputed by the user

printf "Please enter a file name: "
while true
do
    read fileName
    if test -e "$fileName"
    then
        printf "%s exists.\n" "$fileName"
        break
    else
        printf "Please enter a valid file name: "
    fi
done
