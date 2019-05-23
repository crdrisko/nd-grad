#!/bin/bash 
# Name: uinfo.sh - (Listing 6-4)                                           
# Author: Cody R. Drisko (crdrisko)                       
# Date: 05/23/19-11:16:12                                 
# Description: print information about the enviornment

uinfo() #@ USAGE: uinfo [file]
{
  printf "%12s: %s\n" \
    USER	"${USER:-No value assigned}" \
    PWD 	"${PWD:-No value assigned}" \
    COLUMNS	"${COLUMNS:-No value assigned}" \
    LINES	"${LINES:-No value assigned}" \
    SHELL	"${SHELL:-No value assigned}" \
    HOME	"${HOME:-No value assigned}" \
    TERM	"${TERM:-No value assigned}" 
} > ${1:-/dev/fd/1}
