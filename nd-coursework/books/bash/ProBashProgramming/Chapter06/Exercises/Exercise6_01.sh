#!/bin/bash
# Copyright (c) 2019-2025 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: Exercise6_01.sh
# Author: crdrisko
# Date: 07/01/2019-13:45:25
# Description: isvalidip script rewritten with parameter expansion

isvalidip2()     #@ USAGE: isvalidip2 DOTTED-QUAD
{
    case $1 in
        ## reject the following:
        ##  empty string
        ##  anything other than digits and dots
        ##  anything not ending in a digit
        "" | *[!0-9.]* | *[!0-9]) return 1 ;;
    esac

    ## Use parameter expansion to separate the IP address
    var=$1
    varArray=
    for (( i=1; i < 5; ++i ))
    do
        newVar=${var%%.*}
        varArray+=$newVar
        varArray+=" "
        var=${var#*.}
    done

    ## Place the IP address into the positional parameters;
    ## after word splitting each element becomes a parameter
    set -- ${varArray}

    [ $# -eq 4 ] && ## must be four parameters
                    ## each must be less than 256
    ## A default of 666 (which is invalid) is used if a parameter is empty
    ## All four parameters must pass the test
    [ ${1:-666} -le 255 ] && [ ${2:-666} -le 255 ] &&
    [ ${3:-666} -le 255 ] && [ ${4:-666} -le 255 ]
}
