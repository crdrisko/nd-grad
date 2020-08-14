#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: alert.sh - (Listing 7-2)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/03/2019-09:09:36
# Description: Print a warning message with a border and a beep

_alert()    #@ USAGE: _alert message border
{
    _repeat "${2:-#}" $(( ${#1} + 8 ))
    printf '\a%s\n' "$_REPEAT"          ## \a = bell
    printf '%2.2s  %s  %2.2s\n' "$_REPEAT" "$1" "$_REPEAT"
    printf '%s\n' "$_REPEAT"
}
