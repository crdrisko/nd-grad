#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: key-demo.sh - (Listing 15-4)
# Author: Cody R. Drisko (crdrisko)
# Date: 08/10/2019-09:35:18
# Description: Capture function and cursor keys to change colors and move a 
#   block of text around the screen

. key-funcs     ## Source key functions

trap '' 2
trap 'stty sane; printf "${CSI}?12l${CSI}?25h\e[0m\n\n"' EXIT

stty -echo      ## Turn off echoing of user keystrokes
. key-funcs     ## Source key functions

clear           ## Clear the screen
bar=======================================

## Initial position for text block
row=$(( (${LINES:-24} - 10) / 2 ))
col=$(( (${COLUMNS:-80} - ${#bar}) / 2 ))

## Initial colors
fg="${CSI}33m"
fg="${CSI}44m"

## Turn off cursor
printf "%s" "${CSI}?25l"

## Loop until user presses "q"
while :
do
  printf "\e[1m\e[%d;%dH" "$row" "$col"
  printf "\e7 %-${#bar}.${#bar}s ${CSI}0m   \e8\e[1B" "${CSI}0m"
  printf "\e7 $fg$bg%-${#bar}.${#bar}s${CSI}0m \e8\e[1B" "$bar" \
              "" "  Move text with cursor keys" \
              "" "  Change colors with function keys" \
              "" "  Press 'q' to quit" \
              "" "$bar"
  printf "\e7%-${#bar}.${#bar}s     " "${CSI}0m"
  get_key k
  case $k in
    UP) row=$(( $row - 1 )) ;;
    DOWN) row=$(( $row + 1 )) ;;
    LEFT) col=$(( $col - 1 )) ;;
    RIGHT) col=$(( $col + 1 )) ;;
    F1) fg="${CSI}30m" ;;
    F2) bg="${CSI}47m" ;;
    F3) fg="${CSI}31m" ;;
    F4) bg="${CSI}46m" ;;
    F5) fg="${CSI}32m" ;;
    F6) bg="${CSI}45m" ;;
    F7) fg="${CSI}33m" ;;
    F8) bg="${CSI}44m" ;;
    F9) fg="${CSI}35m" ;;
    F10) bg="${CSI}43m" ;;
    F11) fg="${CSI}34m" ;;
    F12) bg="${CSI}42m" ;;
    q|Q) break ;;
  esac
  colmax=$(( ${COLUMNS:-80} - ${#bar} - 4 ))
  rowmax=$(( ${LINES:-24} - 10 ))
  [ $col -lt 1 ] && col=1
  [ $col -gt $colmax ] && col=$colmax
  [ $row -lt 1 ] && row=1
  [ $row -gt $rowmax ] && row=$rowmax
done
