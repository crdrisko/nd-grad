#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: bpl_menu.sh - (Listing 11-4)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/15/2019-10:45:58
# Description: Print menu and execute associated command

bpl_menu()
{
    local IFS=$' \t\n'                      ## Use default setting of IFS
    local num n=1 opt item cmd
    echo

    ## Loop through the command-line arguments
    for item
    do
        printf "  %3d. %s\n" "$n" "${item%%:*}"
        n=$(( $n + 1 ))
    done
    echo

    ## If there are fewer than 10 items, set option to accept key without ENTER
    if [ $# -lt 10 ]
    then
        opt=-sn1
    else
        opt=
    fi
    read -p " (1 to $#) ==> " $opt num      ## Get response from user

    ##Check that user entry is valid
    case $num in
        [qQ0] | "" ) return ;;              ## q, Q, 0, or "" exits
        *[!0-9]* | 0*)                      ## invalid entry
            printf "\aInvalid response: %s\n" "$num" >&2
            return 1
            ;;
    esac
    echo

    if [ "$num" -le "$#" ]                  ## Check that number is <= to the number of menu items
    then
        eval "${!num#*:}"                   ## Execute it using indirect expansion
    else
        printf "\aInvalid response: %s\n" "$num" >&2
        return 1
    fi
}
