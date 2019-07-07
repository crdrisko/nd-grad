#!/bin/bash
# Name: lowword.sh
# Author: Cody R. Drisko (crdrisko)
# Date: 07/06/2019-10:36:28
# Description: Convert word to lowercase

_lowword()
{
    unset _LOWWORD
    local word=$1
    while [ -n "$word" ]    ## loop until nothing is left in $word
    do
        to_lower "$word"
        _LOWWORD=$_LOWWORD$_LWR
        word=${word#?}      ## remove the first character from $word
    done
}

lowword()
{
    _lowword "$@"
    printf "%s\n" "$_LOWWORD"
}