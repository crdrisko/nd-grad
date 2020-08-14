#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: scroll_demo.sh - (Listing 14-7)
# Author: Cody R. Drisko (crdrisko)
# Date: 08/09/2019-08:02:00
# Description: Scrolls a block of text up and then down

. screen-funcs.sh

list=( /usr/bin/* )                     ## try it with other directories or lists
rows=9                                  ## number of rows in scrolling area
delay=.01                               ## delay between scroll advance
width=-33.33                            ## width spec: (no more than) 33 chars, flush left
x=XXXXXXXXXXXXXXXXXXXXXXXXXXX           ## bar of 'X's
x=$x$x$x$x                              ## longer bar

clear                                   ## clear the screen
printf "%50.50s\n" $x{,,,,,,,,,,,,,,}   ## print 14 lines of 'X's
n=0                                     ## start display with first element

## scroll upwards until reaching the bottom
while [ $(( n += 1 )) -lt $(( ${#list[@]} - $rows )) ]
do
  printf "\e[3;1H"
  printf "\e[7C %${width}s\n" "${list[@]:n:rows}"
  read -sn1 -t "$delay" && break
done
sleep 1

## scroll downwards until reaching the top
while [ $(( n -= 1 )) -gt 0 ]
do
  printf "\e[3;1H"
  printf "\e[7C %${width}s\n" "${list[@]:n:rows}"
  read -sn1 -t "$delay" && break
done  

printf "\e[20;1H"                       ## finish with cursor well below scrolling area
