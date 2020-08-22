#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: showvar.sh - (Listing 5-1)
# Author: Cody R. Drisko (crdrisko)
# Date: 06/30/2019-09:30:31
# Description: Print value of variable x

if [ "${x+X}" = X ]     ## If $x is set
then
    if [ -n "$x" ]      ## If $x is not empty
    then
        printf "  \$x = %s\n" "$x"
    else
        printf "  \$x is set but empty\n"
    fi
else
    printf " %s is not set\n" "\$x"
fi
