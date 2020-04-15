#!/bin/bash
# Name: kjvfirsts-awk.sh - (Listing 8-2)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/13/2019-11:03:50
# Description: Print book, chapter, verse, and first words from the KJV

awk -F": ." '   ## -F
{
    split($4,words," ")
    ## printf the first three fields and the first word of the fourth
    printf "%s %s:%s %s\n", $1, $2, $3, words[1]
} ' "$kjv"
