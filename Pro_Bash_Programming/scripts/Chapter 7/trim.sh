#!/bin/bash
# Name: trim.sh - (Listing 7-9)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/04/2019-15:51:28
# Description: Trim unwanted characters

_trim()     #@ Trim spaces (or characters in $2) from $1
{
    local trim_string
    _TRIM=$1
    trim_string=${_TRIM##*[!${2:- }]}
    _TRIM=${_TRIM%"$trim_string"}
    trim_string=${_TRIM%%[!${2:- }]*}
    _TRIM=${_TRIM#"$trim_string"}
}

trim()      #@ Trim spaces (or characters in $2) from $1 and print the result
{
    _trim "$@" && printf "%s\n" "$_TRIM"
}
