#!/bin/bash
# Copyright (c) 2019 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: Exercise10_02.sh - Version 1.0.0
# Author: crdrisko
# Date: 07/14/2019-13:19:22
# Description: Returns successfully if $1 is a valid SAN square


valid_square()
{
    . split_square
    split_square $1
    case $? in
        0) printf "%s is a vaild SAN square\n" "$1" ;;
        1) printf "%s is an invalid SAN square\n" "$1";;
    esac
}

test_valid_square()
{
    local f r
    for f in {a..i}
    do
        for r in {1..9}
        do
            valid_square "$f$r"
        done
        echo
    done
}