#!/bin/bash
# Copyright (c) 2019 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: Exercise7_04.sh - Version 1.0.0
# Author: crdrisko
# Date: 07/07/2019-11:14:57
# Description: Trims characters from a particular side based on the function used

_ltrim()    #@ Trim spaces to the left (or characters in $2) from $1
{
    local ltrim_string
    _LTRIM=$1
    ltrim_string=${_LTRIM##*[!${2:- }]}
    _LTRIM=${_LTRIM%"$ltrim_string"}
    # ltrim_string=${_LTRIM%%[!${2:- }]*}
    # _LTRIM=${_LTRIM#"$ltrim_string"}
}

ltrim()     #@ Trim spaces to the left (or characters in $2) from $1 and print the result
{
    _ltrim "$@" && printf "%s\n" "$_LTRIM"
}


_rtrim()    #@ Trim spaces to the right (or characters in $2) from $1
{
    local rtrim_string
    _RTRIM=$1
    # rtrim_string=${_RTRIM##*[!${2:- }]}
    # _RTRIM=${_RTRIM%"$rtrim_string"}
    rtrim_string=${_RTRIM%%[!${2:- }]*}
    _RTRIM=${_RTRIM#"$rtrim_string"}
}

rtrim()     #@ Trim spaces to the right (or characters in $2) from $1 and print the result
{
    _rtrim "$@" && printf "%s\n" "$_RTRIM"
}
