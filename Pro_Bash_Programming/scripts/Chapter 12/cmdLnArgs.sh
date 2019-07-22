#!/bin/bash
# Name: cmdLnArgs.sh - (Listing 12-2)
# Author: Cody R. Drisko (crdrisko)
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
