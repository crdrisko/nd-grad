#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing7_09.sh
# Author: crdrisko
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
