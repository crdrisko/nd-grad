#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing10_02.sh - Version 1.0.0
# Author: crdrisko
# Date: 07/14/2019-12:18:54
# Description: Convert a SAN-format chess square to a numeric rank and file

split_square()      #@ DESCRIPTION: convert SAN square to numeric rank and file
{                   #@ USAGE: split_square SAN-SQUARE
    local square=$1
    rank=${square#?}
    case $square in
        a[1-8]) file=1 ;; ## Conversion of file to number
        b[1-8]) file=2 ;; ## and checking that the rank is
        c[1-8]) file=3 ;; ## a valid number are done in a
        d[1-8]) file=4 ;; ## single look-up
        e[1-8]) file=5 ;;
        f[1-8]) file=6 ;; ## If the rank is not valid,
        g[1-8]) file=7 ;; ## it falls through to the default
        h[1-8]) file=8 ;;
        *) file=0
           rank=0
           return 1       ## Not a valid square
           ;;
    esac
    return 0
}

test_split_square()
{
    local f r
    for f in {a..i}
    do
        for r in {1..9}
        do
            split_square "$f$r"
            printf "$f$r %d-%d  " "$file" "$rank"
        done
        echo
    done
}
