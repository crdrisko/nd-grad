#!/bin/bash
# Name: dice.sh - (Listing 14-8)
# Author: Cody R. Drisko (crdrisko)
# Date: 08/09/2019-08:21:28
# Description: Defines an array of six dice and places two on the screen

pip=o                               ## character to use for the pips
p0="       "                        ## blank line
p1=" $pip     "                     ## one pip at the left
p2="   $pip   "                     ## one pip in the middle of the line
p3="     $pip "                     ## one pip at the right
p4=" $pip   $pip "                  ## two pips
p5=" $pip $pip $pip "               ## three pips

cs=$'\e7'                           ## save cursor position
cr=$'\e8'                           ## restore cursor position
dn=$'\e[B'                          ## move down 1 line
b=$'\e[1m'                          ## set bold attribute
cu_put='\e[%d;%dH'                  ## format string to position cursor
fgbg='\e[3%d;4%dm'                  ## format string to set colors

dice=(
  ## dice with values 1 to 6 (array elements 0 to 5)
  "$b$cs$p0$cr$dn$cs$p0$cr$dn$cs$p2$cr$dn$cs$p0$cr$dn$p0"
  "$b$cs$p0$cr$dn$cs$p1$cr$dn$cs$p0$cr$dn$cs$p3$cr$dn$p0"
  "$b$cs$p0$cr$dn$cs$p1$cr$dn$cs$p2$cr$dn$cs$p3$cr$dn$p0"
  "$b$cs$p0$cr$dn$cs$p4$cr$dn$cs$p0$cr$dn$cs$p4$cr$dn$p0"
  "$b$cs$p0$cr$dn$cs$p4$cr$dn$cs$p2$cr$dn$cs$p4$cr$dn$p0"
  "$b$cs$p0$cr$dn$cs$p5$cr$dn$cs$p0$cr$dn$cs$p5$cr$dn$p0"
  )

clear
printf "$cu_put" 2 5                ## position cursor
printf "$fgbg" 7 0                  ## white on black
printf "%s\n" "${dice[RANDOM%6]}"   ## print random die

printf "$cu_put" 2 20               ## position cursor
printf "$fgbg" 0 3                  ## black on yellow
printf "%s\n" "${dice[RANDOM%6]}"   ## print random die

printf "\e[0m"
