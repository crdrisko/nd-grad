#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: defVar.sh - (Listing 12-1)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/22/2019-07:42:22
# Description: Example of initialized default variables

## File locations
dict=/usr/share/dict
wordfile=$dict/singlewords
compoundfile=$dict/Compounds

## Default is not to show compound words
compounds=no
