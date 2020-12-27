#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing7_11.sh
# Author: crdrisko
# Date: 07/04/2019-16:11:23
# Description: Convert a month name to its ordinal number

_month2num()
{
    local months=JAN.FEB.MAR.APR.MAY.JUN.JUL.AUG.SEP.OCT.NOV.DEC
    _upword "${1:0:3}"      ## take first three letters of $1 and convert to uppercase
    _index "$months" "$_UPWORD" || return 1
    _MONTH2NUM=$(( $_INDEX / 4 + 1 ))
}

month2num()
{
    _month2num "$@" &&
    printf "%s\n" "$_MONTH2NUM"
}
