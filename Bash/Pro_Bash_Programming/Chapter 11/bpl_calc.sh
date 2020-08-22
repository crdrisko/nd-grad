#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: bpl_calc.sh - (Listing 11-11)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/18/2019-07:50:46
# Description: Print result of arithmetic expression

bpl_calc()      #@ Perform arithmetic, including decimal fractions
{
    local result=$(awk 'BEGIN { OFMT="%f"; print '"$*"'; exit}')
    case $result in
        *.*0) result=${result%"${result##*[!0]}"} ;;
    esac
    printf "%s\n" "$result"
}
