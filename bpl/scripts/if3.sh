#!/bin/bash
# Title: if3 - (Listing 3-3)
# Author: Cody R. Drisko (crdrisko)
# Date: 5/12/2019
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
