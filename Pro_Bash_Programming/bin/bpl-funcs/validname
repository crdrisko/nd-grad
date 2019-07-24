#!/bin/bash
# Name: validname.sh - (Listing 7-6)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/04/2019-11:30:15
# Description: Check $1 for a valid variable or function name

validname()     #@ USAGE: validname varname
    case $1 in 
        ## doesn't begin with letter or underscore, or
        ## contains something not letter, number, or underscore
        [!a-zA-Z_]* | *[!a-zA-z0-9]* ) return 1 ;;
    esac

