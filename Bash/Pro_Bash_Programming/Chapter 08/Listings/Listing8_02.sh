#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing8_02.sh - Version 1.0.0
# Author: crdrisko
# Date: 07/13/2019-11:03:50
# Description: Print book, chapter, verse, and first words from the KJV

awk -F": ." '   ## -F
{
    split($4,words," ")
    ## printf the first three fields and the first word of the fourth
    printf "%s %s:%s %s\n", $1, $2, $3, words[1]
} ' "$kjv"
