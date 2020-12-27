#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing11_07b.sh
# Author: crdrisko
# Date: 07/18/2019-07:50:08
# Description: Using the current directory if no destination is given

bpl_mv()
{
    local final
    if [ $# -eq 1 ]                 ## Only one arg
    then
        command mv -b "$1" .        ## so move it to the current directory
    else
        final=${!#}
        if [ -d "$final" ]          ## if last arg is a directory
        then
            command mv -b "$@"      ## move all the files into it
        else
            command mv -b "$@" .    ## otherwise, move into the current directory
        fi
    fi
}

