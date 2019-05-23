#!/bin/bash
# Title: nmbrScript - (Exercise 3-1)
# Author: Cody R. Drisko (crdrisko)
# Date: 5/12/2019
# Description: asks user for a number until a valid number is given

printf "Please enter a number between 20 and 30: "
while true
do     	
  read number
  if [ $number -lt 20 ]
  then
    printf "%d is too small, please try again: " "$number"
    continue
  elif [ $number -gt 30 ]
  then
    printf "%d is too big, please try again: " "$number"
    continue
  else
    printf "You entered %d\n" "$number" && break
  fi
done

