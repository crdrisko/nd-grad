#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing3_05.sh
# Author: crdrisko
# Date: 06/29/2019-13:36:35
# Description: Is this a valid integer?

case $1 in
    *[!0-9]*) false ;;
    *) true ;;
esac
