#!/bin/bash 
# Name: repeat.sh - (Listing 7-1)                                          
# Author: Cody R. Drisko (crdrisko)                       
# Date: 05/23/19-11:49:55                                 
# Description: Repeat a string N times

_repeat() 
{
  #@ USAGE: _repeat string number
  _REPEAT=$1
  while [ ${#_REPEAT} -lt $2 ] ## Loop until string exceeds desired length
  do
    _REPEAT=$_REPEAT$_REPEAT$_REPEAT  ## 3 seems to be the optimum number
  done
  _REPEAT=${_REPEAT:0:$2}  ## Trim to desired length
}

repeat()
{
  _repeat "$@"
  printf "%s\n" "$_REPEAT"
}

