#!/bin/bash
# Name: promptNumber.sh - (Listing 3-2)
# Author: Cody R. Drisko (crdrisko)
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
