#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: report.sh - (Listing 2-2)
# Author: Cody R. Drisko (crdrisko)
# Date: 06/29/2019-09:22:49
# Description: print formatted sales report

## Build a long string of equals signs
divider=====================================
divider=$divider$divider

## Format strings for printf
header="\n %-10s %11s %8s %10s\n"
format=" %-10s %11.2f %8d %10.2f\n"

## Width of divider
totalWidth=44

## Print categories
printf "$header" ITEM "PER UNIT" NUM TOTAL

## Print divider to match width of report
printf "%$totalWidth.${totalWidth}s\n" "$divider"

## Print lines of report
printf "$format" \
    Chair 79.95 4 319.8 \
    Table 209.99 1 209.99 \
    Armchair 315.49 2 630.98

