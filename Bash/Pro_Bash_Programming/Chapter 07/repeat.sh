#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: repeat.sh - (Listing 7-1)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/02/2019-07:53:50
# Description: Repeat a string N times

_repeat()
{
    #@ USAGE: _repeat string number
    _REPEAT=$1
    while [ ${#_REPEAT} -lt $2 ]            ## Loop until string exceeds desired length
    do
        _REPEAT=$_REPEAT$_REPEAT$_REPEAT    ## 3 seems to be the optimum number
    done
    _REPEAT=${_REPEAT:0:$2}                 ## Trim to desired length
}

repeat()
{
    _repeat "$@"
    printf "%s\n" "$_REPEAT"
}
