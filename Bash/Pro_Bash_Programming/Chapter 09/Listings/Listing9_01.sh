#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing9_01.sh - Version 1.0.0
# Author: crdrisko
# Date: 07/13/2019-11:57:54
# Description: Show busy indicator while waiting for user to press a key

spinner="\|/-"              ## spinner
chars=1                     ## number of characters to display
delay=.15                   ## time in seconds between characters
prompt="press any key..."   ## user prompt
clearline="\e[K"            ## clear to end of line (ANSI terminal)
CR="\r"                     ## carriage return

## loop until user presses a key
until read -sn1 -t$delay -p "$prompt" var
do
    printf "  %.${chars}s$CR" "$spinner"
    temp=${spinner#?}               ## remove first character from $spinner
    spinner=$temp${spinner%"$temp"}  ## and add it to the end
done
printf "$CR$clearline"
