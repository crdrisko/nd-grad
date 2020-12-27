#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing7_08.sh
# Author: crdrisko
# Date: 07/04/2019-15:43:00
# Description: Place one string over the top of another

_overlay()      #@ USAGE: _overlay STRING SUBSTRING START
{               #@ RESULT: IN $_OVERLAY
    local string=$1
    local sub=$2
    local start=$3
    local left right
    left=${string:0:start-1}
    right=${string:start+${#sub}-1}
    _OVERLAY=$left$sub$right
}

overlay()       #@ USAGE: overlay STRING SUBSTRING START
{
    _overlay "$@" && printf "%s\n" "$_OVERLAY"
}
