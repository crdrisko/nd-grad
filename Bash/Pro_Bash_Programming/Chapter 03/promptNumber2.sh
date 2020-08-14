#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: promptNumber2.sh - (Listing 3-3)
# Author: Cody R. Drisko (crdrisko)
# Date: 06/29/2019-13:26:21
# Description: Prompt for a number and check that it is within a given range

printf "Enter a number between 10 and 20 inclusive: "
read number
if [ "$number" -lt 10 ]
then
    printf "%d is too low\n" "$number" >&2
    exit 1
elif [ "$number" -gt 20 ]
then
    printf "%d is too high\n" "$number" >&2
    exit 1
else
    printf "You entered %d\n" "$number"
fi
