#!/bin/bash
# Title: if2 - (Listing 3-2)
# Author: Cody R. Drisko (crdrisko)
# Date: 5/12/2019
# Description: Prompt for a number and check that it is no greater than 10

printf "Enter a number no greater than 10: "
read number
if [ "$number" -gt 10 ]
then
  printf "%d is too big\n" "$number" >&2
  exit 1
else
  printf "You entered %d\n" "$number"
fi
