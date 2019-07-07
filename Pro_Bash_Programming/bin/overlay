#!/bin/bash
# Name: overlay.sh - (Listing 7-8)
# Author: Cody R. Drisko (crdrisko)
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
