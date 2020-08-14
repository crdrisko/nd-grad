#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: varfuncs.sh - (Listing 9-2)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/13/2019-12:10:22
# Description: Emulate assciative arrays

validname() ## Borrowed from Chapter 7
    case $1 in 
        [!a-zA-Z_]* | *[!a-zA-Z0-9_]* ) return 1 ;;
    esac

setvar()    #@ DESCRIPTION: assign value to supplied name
{           #@ USAGE: setvar varname value
    validname "$1" || return 1
    eval "$1=\$2"
}

getvar()    #@ DESCRIPTION: print value assigned to varname
{           #@ USAGE: getvar varname
    validname "$1" || return 1
    eval "printf '%s\n' \"\${$1}\""
}

echo "Assigning some values"
for n in {1..3}
do
    setvar "var_$n" "$n - $RANDOM"
done

echo "Variables assigned; printing values:"
for n in {1..3}
do
    getvar "var_$n"
done
