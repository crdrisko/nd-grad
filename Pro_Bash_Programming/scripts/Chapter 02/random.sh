#!/bin/bash
# Name: random.sh - (Exercise 2-2)
# Author: Cody R. Drisko (crdrisko)
# Date: 06/29/2019-09:40:44
# Description: prints 8 random numbers to both a file and a variable

printf -v var "%5s.%-5s\n" "$RANDOM" "$RANDOM" "$RANDOM" "$RANDOM"  \
    "$RANDOM" "$RANDOM" "$RANDOM" "$RANDOM"
printf "%s" "$var" | tee randomFile 
