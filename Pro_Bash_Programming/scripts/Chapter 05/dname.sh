#!/bin/bash
# Name: dname.sh - (Listing 5-3)
# Author: Cody R. Drisko (crdrisko)
# Date: 06/30/2019-09:58:53
# Description: Print the directory portion of a file path

case $1 in
    */*) printf "%s\n" "${1%/*}" ;;
    *) [ -e "$1" ] && printf "%s\n" "$PWD" || echo '.' ;;
esac
