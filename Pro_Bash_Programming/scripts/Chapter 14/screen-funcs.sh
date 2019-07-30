#!/bin/bash
# Name: screen-funcs.sh - (Listing 14-1)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/29/2019-13:26:55
# Description: Library of screen manuipulation functions


## Sourcing the screen-vars libray - (Listing 14-1a)
. screen-vars.sh


## Place the cursor at a specified location and print optional string - (Listing 14-1b)
printat()       #@ USAGE: printat [row [column [string]]]
{
  printf "${cu_row_col?}" ${1:-1} ${2:-1}
  if [ $# -gt 2 ]
  then 
    shift 2
    printf "%s" "$*"
  fi
}



