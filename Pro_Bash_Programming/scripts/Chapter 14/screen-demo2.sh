#!/bin/bash
# Name: screen-demo2.sh - (Listing 14-4)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/29/2019-13:59:38
# Description: Second demo manipulating the screen

. screen-funcs.sh
echo
for attr in "$underline" 0 "$reverse" "$bold"
do
  printf "$set_attr" "$attr"
  printf "$set_fg %s " "$red" RED
  printf "$set_fg %s " "$green" GREEN
  printf "$set_fg %s " "$blue" BLUE
  printf "$set_fg %s " "$black" BLACK
  printf "\e[m\n"
done
echo
