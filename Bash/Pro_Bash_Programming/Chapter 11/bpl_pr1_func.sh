#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: bpl_pr1_func.sh - (Listing 11-9)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/18/2019-07:50:38
# Description: Function to print its arguments one to a line

bpl_pr1()
{
    case $1 in
         -w) pr_w=                          ## width specification modifier
             shift
             ;;
         -W) pr_w=${2}
             shift 2
             ;;
        -W*) pr_w=${1#??}
             shift
             ;;
          *) pr_w=-.${COLUMNS:-80}          ## default to number of columns in window 
             ;;
    esac
    printf "%${pr_w}s\n" "$@"
}
