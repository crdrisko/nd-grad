#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: bpl_md.sh - (Listing 11-8)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/18/2019-07:50:12
# Description: Create a new directory and intermediate directories and optionally cd into it

bpl_md() { #@ create new directory, including intermediate directories if necessary
    case $1 in
        -c) mkdir -p "$2" && cd "$2" ;; 
         *) mkdir -p "$@" ;;
    esac
}
