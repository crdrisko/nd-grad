#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: bpl_cp.sh - (Listing 11-7a)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/18/2019-07:50:04
# Description: Using the current directory if no destination is given

bpl_cp()
{
    local final
    if [ $# -eq 1 ]                 ## Only one arg
    then
        command cp -b "$1" .        ## so copy it to the current directory
    else
        final=${!#}
        if [ -d "$final" ]          ## if last arg is a directory
        then
            command cp -b "$@"      ## copy all the files into it
        else
            command cp -b "$@" .    ## otherwise, copy into the current directory
        fi
    fi
}
