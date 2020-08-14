#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: screen-demo3.sh - (Listing 14-5)
# Author: Cody R. Drisko (crdrisko)
# Date: 08/01/2019-07:59:39
# Description: Third demo manipulating the screen

. screen-funcs.sh

printf "$cls"
put_block_at 3 12 First Second Third Fourth Fifth
put_block_at 2 50 January February March April May June July
