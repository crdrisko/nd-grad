#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing12_06.sh
# Author: crdrisko
# Date: 07/22/2019-08:14:10
# Description: Parsing configuration file (Listing12_05.cfg)

IFS=$'\n'
file=Listing12_05.cfg
settings=( $( < "$file" ) )             ## store file in array, 1 line per element
eval "${settings[@]%%#*}"               ## extract and execute the assignments
comments=( "${settings[@]#*## }" )      ## store comments in array

## Print the comments
printf "%s\n" "${comments[@]}"
