#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing11_03.sh
# Author: crdrisko
# Date: 07/14/2019-13:53:09
# Description: Select new directory from a menu of those already visited

bpl_cdm() #@ select new directory from a menu of those already visited
{
    local dir IFS=$'\n' item
    for dir in $(dirs -l -p)                ## loop through directories in DIRSTACK[@]
    do
        [ "$dir" = "$PWD" ] && continue     ## skip current directory
        case ${item[*]} in
            *"$dir:"*) ;;                   ## $dir already in array; do nothing
            *) item+=( "$dir:cd '$dir'" )   ## add $dir to array
        esac
    done
    menu "${item[@]}" Quit:                 ## pass array to menu function
}
