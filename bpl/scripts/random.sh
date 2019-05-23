#!/bin/bash
# Title: random - (Exercise 2-2)
# Author: 
# Date: 5/11/2019
# Description: writes numbers to both a file and to a variable using $RANDOM

printf -v rndmNum "%10s.%-10s\n" "$RANDOM" "$RANDOM" "$RANDOM" "$RANDOM" \
	"$RANDOM" "$RANDOM" "$RANDOM" "$RANDOM"
printf "%s\n" "$rndmNum" | tee rndmFile
