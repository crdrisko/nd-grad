#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing14_03.sh
# Author: crdrisko
# Date: 07/29/2019-13:59:38
# Description: First demo manipulating the screen

. screen-funcs.sh                               ## source the screen-funcs library
printf "$clear$cu_hide"                         ## clear the screen and hide the cursor
printat 10 10 "${cu_save}XX"                    ## move, save position, and print XX
sleep 1                                         ## ZZZZZZZZ
printat 20 20 "20/20"                           ## move and print
sleep 1                                         ## ZZZZZZZZ
printf "$cu_restore$cu_down${cu_save}YY"        ## restore pos., move, print, save pos.
sleep 1                                         ## ZZZZZZZZ
printf "$cu_restore$cu_down${cu_save}ZZ" 4      ## restore pos., move, print, save pos.
sleep 1                                         ## ZZZZZZZZ
printat 1 1 "$cu_show"                          ## move to top left and show cursor
