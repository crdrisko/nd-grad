#!/bin/bash
# Name: wfe.sh - (Example 10-1)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/13/2019-20:28:41
# Description: A sample script with all necessary components


### Comments ###
#:       Title: wfe - List words ending with REGEX
#:    Synopsis: wfe [-c|-h|-v] REGEX 
#:        Date: 2009-04-13
#:     Version: 1.0
#:      Author: Chris F.A. Johnson
#:     Options: -c - Include compound words
#:              -h - Print usage information
#:              -v - Print version number


### Initialization of Variables ###
## Script metadata
scriptname=${0##*/}
description="List words ending with REGEX"
usage="$scriptname [-c|-h|-v] REGEX"
date_of_creation=2009-04-13
version=1.0
author="Chris F.A. Johnson"

## File locations
dict=$HOME/bpl/words
wordfile=$dict/singlewords
compoundfile=$dict/Compounds

## Default is not to show compound words
compounds=


### Function Definitions ###
die()       #@ DESCRIPTION: print error message and exit with supplied return code
{           #@ USAGE: die STATUS [MESSAGE]
    error=$1
    shift
    [ -n "$*" ] printf "%s\n" "$*" >&2
    exit "$error"
}

usage()     #@ DESCRIPTION: print versio information
{           #@ USAGE: usage
            #@ REQUIRES: variable defined: $scriptname
    printf "%s - %s\n" "$scriptname" "$description"
    printf "USAGE: %s\n" "$usage"
}

version()   #@ DESCRIPTION: print version information
{           #@ USAGE: version
            #@ REQUIRES: variables defined: $scriptname, $author, and $version
    printf "%s version %s\n" "$scriptname" "$version"
    printf "by %s, %d\n" "$author" "${date_of_creation%%-*}"
}


### Runtime Configuration and Options ###
## Parse command-line options, -c, -h, and -v
while getopts chv var
do
    case $var in
        c) compounds=$compoundfile ;;
        h) usage; exit ;;
        v) version; exit ;;
    esac
done
shift $(( $OPTIND - 1 ))

## Regular expression supplied on the command line
regex=$1

## Check that the user entered a search term
if [ -z "$regex" ]
then
    {
      echo "Search term missing"
      usage
    } >&2
    exit 1
fi 


### Process Information ###
## Search $wordfile and $compounds if it is defined
{
    cat "$wordfile"
    if [ -n "$compounds" ]
    then
        cut -f1 "$compounds"
    fi
} | grep -i ".$regex$" |
 sort -fu ## Case-insensitive sort; remove duplicates
