#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing13_02.sh - Version 1.0.0
# Author: crdrisko
# Date: 07/27/2019-09:49:08
# Description: Sort command-line arguments

isort()
{
  local -a a
  a=( "$1" )            ## put first argument in array for initial comparison
  shift                 ## remove first argument
  for e                 ## for each of the remaining arguments ...
  do
    if [ "$e" \< "${a[0]}" ]                  ## does it precede the first element?
    then
      a=( "$e" "${a[@]}" )                    ## if yes, put it first
    elif [ "$e" \> "${a[${#a[@]}-1]}" ]       ## if no, does it go at the end
    then
      a=( "${a[@]}" "$e" )                    ## if yes, put it at the end
    else                                      ## otherwise,
      n=0
      while [ "${a[$n]}" \< "$e" ]            ## find where it goes
      do
        n=$(( $n + 1 ))
      done
      a=( "${a[@]:0:n}" "$e" "${a[@]:n}" )    ## and put it there
    fi
  done
  printf "%s\n" "${a[@]}"
}
