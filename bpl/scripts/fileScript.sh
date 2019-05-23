#!/bin/bash
# Title: fileScript - (Exercise 3-2)
# Author: Cody R. Drisko (crdrisko)
# Date: 5/12/2019
# Description: attempts to find a file

printf "Enter a file name: "
while true
do
  read fileName
  if test -e $fileName
  then
    printf "%s is a valid file.\n" "$fileName"
    break
  else
    printf "%s is not a valid file, please try again: " "$fileName"
  fi
done

