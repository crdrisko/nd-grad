#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: bpl_cd.sh - (Listing 11-1)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/14/2019-13:34:02
# Description: Change directory, saving location on the directory stack

bpl_cd()    #@ Change directory, storing new directory on DIRSTACK
{
    local dir error             ## variables for directory and return code

    while :                     ## ignore all options
    do 
        case $1 in 
            --) break ;;
            -*) shift ;;
             *) break ;;
        esac
    done

    dir=$1

    if [ -n "$dir" ]            ## if a $dir is not empty
    then
        pushd "$dir"            ## change directory
    else
        pushd "$HOME"           ## go HOME if nothing on the command line
    fi 2> /dev/null             ## error message should come from cd, not pushd

    error=$?                    ## store pushd's exit code

    if [ $error -ne 0 ]         ## failed, print error message
    then
        builtin cd "$dir"       ## let the builtin cd provide the error message
    fi
    return "$error"             ## leave with pushd's exit code
} > /dev/null
