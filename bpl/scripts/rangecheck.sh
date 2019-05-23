#!/bin/bash 
# Name: rangecheck.sh - (Listing 6-3)                                          
# Author: Cody R. Drisko (crdrisko)                       
# Date: 05/23/19-11:00:36                                 
# Description: Check whether an integer is within a specified range

rangecheck() #@ USAGE: rangecheck int [low [high]]
  if [ "$1" -lt ${2:-10} ]
  then
    return 1
  elif [ "$1" -gt ${3:-20} ]
  then
    return 2
  else
    return 0
  fi                                          


