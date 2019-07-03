#!/bin/bash
# Name: uinfo.sh - (Listing 6-4)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/01/2019-12:49:37
# Description: Print information about the enviornment 

uinfo()     #@ USAGE: uinfo [file]
{
    printf "%12s: %s\n" \
        USER    "${USER:-No value assigned}" \
        PWD     "${PWD:-No value assigned}" \
        COLUMNS "${COLUMNS:-No value assigned}" \
        LINES   "${LINES:-No value assigned}" \
        SHELL   "${SHELL:-No value assigned}" \
        HOME    "${HOME:-No value assigned}" \
        TERM    "${TERM:-No value assigned}"
} > ${1:-/dev/fd/1}
