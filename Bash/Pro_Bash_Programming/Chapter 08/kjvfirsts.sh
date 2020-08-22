#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: kjvfirsts.sh - (Listing 8-1)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/07/2019-16:38:21
# Description: Print book, chapter, verse, and first words from KJV

while IFS=": ." read book chapter verse text
do
    firstword=${text%% *}
    printf "%s %s:%s %s\n" "$book" "$chapter" "$verse" "$firstword"
done < "$kjv"
