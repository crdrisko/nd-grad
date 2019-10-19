#!/usr/local/bin/bash
# Name: lettersort.sh - (Listing 13-1)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/26/2019-07:38:45
# Description: Sort letters in a word alphabetically

lettersort()    #@ Sort letters in $1, store in $2
{
  local letter string
  declare -A letters
  string=${1:?}
  while [ -n "$string" ]
  do
    letter=${string:0:1}
    letters["$letter"]=${letters["$letter"]}$letter
    string=${string#?}
  done
  printf -v "${2:-_LETTERSORT}" "%s" "${letters[@]}"    
}
