#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing6_04.sh - Version 1.0.0
# Author: crdrisko
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
