#!/bin/bash 
# Name: dname.sh - (Listing 5-3)                                          
# Author: Cody R. Drisko (crdrisko)                       
# Date: 05/18/19-18:49:00                                 
# Description: Print the directory portion of a file path

case $1 in
  */*) printf "%s\n" "${1%/*}" ;;
  *) [ -e "$1" ] && printf "%s\n" "$PWD" || echo '.' ;;
esac


