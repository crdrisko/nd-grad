#!/bin/bash
# Name: kjvfirsts.sh - (Listing 8-1)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/07/2019-16:38:21
# Description: Print book, chapter, verse, and first words from KJV

while IFS=": ." read book chapter verse text
do
    firstword=${text%% *}
    printf "%s %s:%s %s\n" "$book" "$chapter" "$verse" "$firstword"
done < "$kjv"
