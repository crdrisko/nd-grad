#!/bin/bash
# Name: getlines.sh - (Listing 13-4)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/27/2019-11:58:05
# Description: Store a range of lines from a file in an array

if [ "${BASH_VERSINFO[0]}" -gt 4 ]
then
  getlines()    #@ USAGE: getlines file start num arrayname
  {
    mapfile -t -s$(( $2 - 1 )) -n ${3:?} "$4" < "$1"
  }
else
  getlines()    #@ USAGE: getlines file start num arrayname
  {
    local IFS=$'\n' getlinearray arrayname=${4:?}
    getlinearray=( $(sed -n "$2,$(( $2 - 1 + $3 )) p" "$1") )
    eval "$arrayname=( \"\${getlinearray[@]}\" )"
  }
fi
