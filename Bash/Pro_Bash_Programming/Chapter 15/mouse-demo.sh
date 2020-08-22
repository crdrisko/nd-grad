#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: mouse-demo.sh - (Listing 15-6)
# Author: Cody R. Drisko (crdrisko)
# Date: 08/12/2019-07:45:51
# Description: An example of reading mouse clicks

ESC=$'\e'
but_row=1

mv=9                            ## mv = 1000 for press and release reporting; mv=9 for press only
_STTY=$(stty -g)                ## save current terminal setup
stty -echo -icanon              ## turn off line buffering
printf "${ESC}[?${mv}h      "   ## turn on mouse reporting
printf "${ESC}[?25l"            ## turn off cursor

printat()   #@ USAGE: printat ROW COLUMN
{
  printf "${ESC}[${1};${2}H"
}

print_buttons()
{
  num_but=$#
  gutter=2
  gutters=$(( $num_but + 1 ))
  but_width=$(( ($COLUMNS - $gutters) / $num_but ))
  n=0
  for but_str
  do
    col=$(( $gutter + $n * ($but_width + $gutter) ))
    printat $but_row $col
    printf "${ESC}[7m%${but_width}s" " "
    printat $but_row $(( $col + ($but_width - ${#but_str}) / 2 ))
    printf "%.${but_width}s${ESC}[0m" "$but_str"
    n=$(( $n + 1 ))
  done    
}

printf "${ESC}[H${ESC}[J"
while :
do
  [ $mv -eq 9 ] && mv_str="Click to Show Press & Release" ||
                   mv_str="Click to Show Press Only"
  print_buttons "$mv_str" "Exit"

  read -n6 x
  m1=${x#???}                   ## Remove the first 3 characters
  m2=${x#????}                  ## Remove the first 4 characters
  m3=${x#?????}                 ## Remove the first 5 characters

  ## Convert to characters to decimal values
  printf -v mb "%d" "'$m1"
  printf -v mx "%d" "'$m2"
  printf -v my "%d" "'$m3"

  ## Values > 127 are signed
  [ $mx -lt 0 ] && MOUSEX=$(( 223 + $mx )) || MOUSEX=$(( $mx - 32 ))
  [ $my -lt 0 ] && MOUSEY=$(( 223 + $my )) || MOUSEY=$(( $my - 32 ))

  ## Button pressed is in first 2 bytes; use bitwise AND
  BUTTON=$(( ($mb & 3) + 1 ))
  case $MOUSEY in
    $but_row) ## Calculate which on-screen button has been pressed
              button=$(( ($MOUSEX - $gutter) / $but_width + 1 ))
              case $button in
                1) printf "${ESC}[?${mv}l"
                   [ $mv -eq 9 ] && mv=1000 || mv=9
                   printf "${ESC}[?${mv}h"
                   [ $mv -eq 1000 ] && x=$(dd bs=1 count=6 2>/dev/null)
                   ;;
                2) break ;;
              esac
              ;;
    *) printat $MOUSEY $MOUSEX
       printf "X=%d Y=%d [%d]   " $MOUSEX $MOUSEY $BUTTON
  esac
done

printf "${ESC}[?${mv}l"         ## Turn off mouse reporting
stty "$_STTY"                   ## Restore terminal settings
printf "${ESC}[?12l${ESC}[?25h" ## Turn cursor back on
printf "\n${ESC}[0J\n"          ## Clear from cursor to bottom of screen
