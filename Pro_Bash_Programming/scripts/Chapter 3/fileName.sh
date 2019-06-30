#!/bin/bash
# Name: fileName.sh - (Exercise 3-2)
# Author: Cody R. Drisko (crdrisko)
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
