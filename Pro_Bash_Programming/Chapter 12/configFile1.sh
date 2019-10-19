#!/bin/bash
# Name: configFile.sh - (Listing 12-6)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/22/2019-08:14:10
# Description: Parsing configuration file (words.cfg)

IFS=$'\n'
file=words.cfg
settings=( $( < "$file" ) )             ## store file in array, 1 line per element
eval "${settings[@]%%#*}"               ## extract and execute the assignments
comments=( "${settings[@]#*## }" )      ## store comments in array

## Print the comments
printf "%s\n" "${comments[@]}"
