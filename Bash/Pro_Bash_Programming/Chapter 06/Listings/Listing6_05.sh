#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing6_05.sh - Version 1.0.0
# Author: crdrisko
# Date: 07/01/2019-12:59:24
# Description: Sort three integers

_max3() { #@ Sort three integers and store in $_MAX3, $_MID3, and $_MIN3
    [ $# -ne 3 ] && return 5
    [ $1 -gt $2 ] && { set -- $2 $1 $3; }
    [ $2 -gt $3 ] && { set -- $1 $3 $2; }
    [ $1 -gt $2 ] && { set -- $2 $1 $3; }
    _MAX3=$3
    _MID3=$2
    _MIN3=$1
}
