#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing7_10.sh
# Author: crdrisko
# Date: 07/04/2019-16:05:27
# Description: Return position of one string inside another

_index()    #@ Store position of $2 in $1 in $_INDEX
{
    local idx
    case $1 in
        "") _INDEX=0; return 1 ;;
        *"$2"*) ## extract up to beginning of the matching portion
                idx=${1%%"$2"*}
                ## the starting position is one more than the length
                _INDEX=$(( ${#idx} + 1 )) ;;
        *) _INDEX=0; return 1 ;;
    esac
}

index()
{
    _index "$@"
    printf "%d\n" "$_INDEX"
}
