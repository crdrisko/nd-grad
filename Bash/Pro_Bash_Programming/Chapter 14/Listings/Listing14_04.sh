#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing14_04.sh - Version 1.0.0
# Author: crdrisko
# Date: 07/29/2019-13:59:38
# Description: Second demo manipulating the screen

. screen-funcs.sh
echo
for attr in "$underline" 0 "$reverse" "$bold" "$bold;$reverse"
do
  printf "$set_attr" "$attr"
  printf "$set_fg %s " "$red" RED
  printf "$set_fg %s " "$green" GREEN
  printf "$set_fg %s " "$blue" BLUE
  printf "$set_fg %s " "$black" BLACK
  printf "\e[m\n"
done
echo
