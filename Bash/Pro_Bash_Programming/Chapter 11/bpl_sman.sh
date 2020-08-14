#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: bpl_sman.sh - (Listing 11-12)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/18/2019-07:50:50
# Description: Call up a man page and search for a pattern

bpl_sman()      #@ USAGE: sman command search_pattern
{
    LESS="$LESS${2:+ +/$2}" man "$1"
}
