#!/bin/bash
# Copyright (c) 2019 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: _max3V2.sh
# Author: crdrisko
# Date: 07/01/2019-15:03:00
# Description: Sort three integers after checking that they are valid

_max3V2() #@ Sort three integers and store in $_MAX3, $_MID3, and $_MIN3
{
    _MAX3=
    _MID3=
    _MIN3=
    for i in $@
    do
        case ${i#-} in
            *[!0-9]*) printf "All arguments must be integers.\n"
                      return 4;;
            *) ;;
        esac
    done

    if [ "$?" -ne 4 ]
    then
        [ $# -ne 3 ] && return 5
        [ $1 -gt $2 ] && { set -- $2 $1 $3; }
        [ $2 -gt $3 ] && { set -- $1 $3 $2; }
        [ $1 -gt $2 ] && { set -- $2 $1 $3; }
        _MAX3=$3
        _MID3=$2
        _MIN3=$1
        printf "%s > %s > %s\n" "$_MAX3" "$_MID3" "$_MIN3"
    fi
}
