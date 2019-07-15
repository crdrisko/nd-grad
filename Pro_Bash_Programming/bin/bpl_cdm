#!/bin/bash
# Name: bpl_cdm.sh - (Listing 11-3)
# Author: Cody R. Drisko (crdrisko)
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
