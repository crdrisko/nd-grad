#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing3_01.sh
# Author: crdrisko
# Date: 06/29/2019-13:18:24
# Description: Read and check input

read name
if [ -z "$name" ]
then
    echo "No name entered" >&2
    exit 1                      ## Set a failed return code
fi
