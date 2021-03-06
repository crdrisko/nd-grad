#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing11_06.sh
# Author: crdrisko
# Date: 07/18/2019-07:49:59
# Description: List most recently modified files

num=10                                              ## number of files to print
short=0                                             ## set to 1 for short listing
timestyle='--time-style="+ %d-%b-%Y %H:%M%S "'      ## GNU-specific time format

opts=Aadn:os

while getopts $opts opt
do 
    case $opt in
        a|A|d) ls_opts="$ls_opts -$opt" ;;          ## options passed to ls
        n) num=$OPTARG ;;                           ## number of files to display
        o) ls_opts="$ls_opts -r" ;;                 ## show oldest files, not newest
        s) short=$(( $short + 1 )) ;;
    esac
done
shift $(( $OPTIND - 1 ))

case $short in
    0) ls_opts="$ls_opts -l -t" ;;                  ## long listing, use -l
    *) ls_opts="$ls_opts -t" ;;                     ## short listing, do not use -l
esac

ls $ls_opts $timestyle "$@" | {
    read                                            ## In bash, the same as: IFS= read -r REPLY
    case $line in 
        total*) ;;                                  ## do not display the 'total' line
        *) printf "%s\n" "$REPLY" ;;
    esac
    cat
} | head -n$num
