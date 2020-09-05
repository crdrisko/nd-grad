#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing11_10.sh - Version 1.0.0
# Author: crdrisko
# Date: 07/18/2019-07:50:20
# Description: Script to print its arguments one to a line

while getopts wW: opt
do
    case $opt in 
        w) w=
           shift
           ;;
        W) w=$OPTARG ;;
        *) w=-.${COLUMNS:-80} ;;
    esac
done
shift $(( $OPTIND - 1 ))

printf "%${w}s\n" "$@"
