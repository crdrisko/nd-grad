#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: readpgn.sh - (Listing 13-9)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/29/2019-07:30:29
# Description: Parse a PGN game and print game in a column

pgnfile="${1:?}"
header=0
game=0

gettag()        #@ Create a variable with the same name and value as the tag
{
  local tagline=$1
  tag=${tagline%% *}                        ## get line before the first space
  tag=${tag#?}                              ## remove the open bracket                    
  IFS='"' read a val b <<.  
   $tagline
.                                           ## get the 2nd field, using " as delimiter

  eval "$tag=\$val"
}

{
  while IFS= read -r line
  do
    case $line in
      \[*) gettag "$line" ;;
       "") [ -n "$Event" ] && break ;;      ## skip blank lines at beginning of file
    esac
  done
  mapfile -t game                           ## read remainder of the file
} < "$pgnfile"

## Remove blank lines from end of array
while [ -z "${game[${#game[@]}-1]}" ]
do
  unset game[${#game[@]}-1]
done

## Print the game with header
echo "Event: $Event"
echo "Date:  $Date"
echo
set -f
printf "%4s  %-10s %-10s\n" "" White Black ""  ========== ========== \
          "" "$White" "$Black" ${game[@]:0:${#game[@]}-1}
printf "%s\n" "${game[${#game[@]}-1]}"
