#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing3_02.sh
# Author: crdrisko
# Date: 06/29/2019-13:22:12
# Description: Prompt for a number and check that it is no greater than ten

printf "Enter a number no greater than 10: "
read number
if [ "$number" -gt 10 ]
then
    printf "%d is too big\n" "$number" >&2
    exit 1
else
    printf "You entered %d\n" "$number"
fi
