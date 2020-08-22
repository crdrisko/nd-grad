#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: upword.sh - (Listing 7-5)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/03/2019-10:51:31
# Description: Convert word to uppercase

_upword()   #@ USAGE: upword STRING
{
    unset _UPWORD
    local word=$1
    while [ -n "$word" ]    ## loop until nothing is left in $word
    do
        to_upper "$word"
        _UPWORD=$_UPWORD$_UPR
        word=${word#?}      ## remove the first character from $word
    done
}

upword()
{
    _upword "$@"
    printf "%s\n" "$_UPWORD"
}

