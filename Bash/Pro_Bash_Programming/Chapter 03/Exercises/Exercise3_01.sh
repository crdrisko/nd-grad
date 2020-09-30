#!/bin/bash
# Copyright (c) 2019 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: Exercise3_01.sh
# Author: crdrisko
# Date: 06/29/2019-13:45:02
# Description: Checks to see if a valid number between 20 and 30 was entered

printf "Please enter a number between 20 and 30 inclusive: "
while true
do
    read number
    if [ "$number" -ge 20 ] && [ "$number" -le 30 ]
    then
        printf "You entered %d\n"  "$number"
        break
    else
        printf "Please enter a valid number: "
    fi
done
