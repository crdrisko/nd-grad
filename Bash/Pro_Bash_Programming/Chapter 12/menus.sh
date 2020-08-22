#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: menus.sh - (Listing 12-3)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/22/2019-07:48:21
# Description: Set parameters via menu

while :         ## loop until user presses 'q'
do 
    bar=======================================================================
    ## Print menu
    printf "\n\n%s\n" "$bar"
    printf "  Dictionary parameters\n"
    printf "%s\n\n" "$bar"
    printf "  1. Directory containing dictionary: %s\n" "$dict"
    printf "  2. File containing word list: %s\n" "$wordfile"
    printf "  3. File containing compound words and phrases: %s\n" "$compoundfile"
    printf "  4. Include compound words and phrases in results? %s\n" "$compounds"
    printf "  q. %s\n" "Exit Menu"
    printf "\n%s\n\n" "$bar"

    ## Get user response
    read -sn1 -p "Select (1, 2, 3, 4, q): " input
    echo

    ## Interpret user response
    case $input in 
        1) read -ep "Enter dictionary directory: " dict ;; 
        2) read -ep "Enter word-list file: " wordfile ;;
        3) read -ep "Enter compound-word file: " compoundfile ;;
        4) [ "$compounds" = y ] && compounds=n || compounds=y ;;
        q) break ;;
        *) printf "\n\aInvalid selection: %c\n" "$input" >&2
           sleep 2
           ;;
    esac
done
