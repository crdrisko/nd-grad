#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing12_02.sh
# Author: crdrisko
# Date: 07/22/2019-07:45:47
# Description: Parse command-line options

while getopts d:w:f:c var
do
    case "$var" in
        c) compounds=1 ;;
        d) dict=$OPTARG ;;
        w) wordfile=$OPTARG ;;
        f) compoundfile=$OPTARG ;;
    esac
done
