#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing11_13.sh - Version 1.0.0
# Author: crdrisko
# Date: 07/18/2019-07:51:00
# Description: Look up a man page in the POSIX Spec

bpl_sus()
{
    local html_file=/usr/share/sus/$1.html          ## adjust to taste
    local dir=9699919799
    local sus_dir=http://www.opengroup.org/onlinepubs/$dir/utilities/
    [ -f "$html_file" ] ||
        lynx -source $sus_dir${1##*/}.html > $html_file ##>/dev/null 2>&1
    lynx -dump -nolist $html_file | ${PAGER:-less}
}
