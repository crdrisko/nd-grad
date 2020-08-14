#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: parseopts.sh - (Listing 4-3)
# Author: Cody R. Drisko (crdrisko)
# Date: 06/29/2019-17:32:34
# Description: Parse command-line options

progname=${0##*/}                       ## Get the name of the script without its path

## Default values
verbose=0
filename=

## List of options the program will accept;
## those options that take arguments are followed by a colon
optstring=f:v

## The loop calls getopts until there are no more options on the command line
## Each option is stored in $opt, any option arguments are stored in OPTARG
while getopts $optstring opt
do
    case $opt in
        f) filename=$OPTARG ;;          ## OPTARG contains the argument to the option
        v) verbose=$(( $verbose + 1 )) ;;
        *) exit 1 ;;
    esac
done

## Remove options from the command line
## $OPTIND points to the next, unparsed argument
shift "$(( $OPTIND - 1 ))"

## Check whether a filename was entered
if [ -n "$filename" ]
then
    if [ $verbose -gt 0 ]
    then
        printf "Filename is %s\n" "$filename"
    fi
else
    if [ $verbose -gt 0 ]
    then
        printf "No filename entered\n" >&2
    fi
    exit 1
fi

## Check whether file exists
if [ -f "$filename" ]
then
    if [ $verbose -gt 0 ]
    then
        printf "Filename %s found\n" "$filename"
    fi
else
    if [ $verbose -gt 0 ]
    then
        printf "File, %s, does not exist\n" "$filename" >&2
    fi
    exit 2
fi

## If the verbose option is selected,
## print the number of arguments remaining on the command line
if [ $verbose -gt 0 ]
then
    printf "Number of arguments is %d\n" "$#"
fi