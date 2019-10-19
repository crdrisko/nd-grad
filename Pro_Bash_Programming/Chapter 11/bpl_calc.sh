#!/bin/bash
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
