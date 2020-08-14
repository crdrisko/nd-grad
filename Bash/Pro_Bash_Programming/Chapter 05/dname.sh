#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: dname.sh - (Listing 5-3)
# Author: Cody R. Drisko (crdrisko)
# Date: 06/30/2019-09:58:53
# Description: Print the directory portion of a file path

case $1 in
    */*) printf "%s\n" "${1%/*}" ;;
    *) [ -e "$1" ] && printf "%s\n" "$PWD" || echo '.' ;;
esac
