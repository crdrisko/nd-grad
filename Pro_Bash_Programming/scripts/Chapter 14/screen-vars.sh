#!/bin/bash
# Name: screen-vars.sh - (14-2)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/29/2019-13:33:07
# Description: Library of screen manuipulation variables


## Screen variable definitions - (Listing 14-2a)
ESC=$'\e'
CSI=$ESC[
cu_row_col=$'\e[%d;%dH'


## Variable definitions for erasing all or part of the screen - (Listing 14-2b)
topleft=${CSI}H                         ## move cursor to top left corner of screen
cls=${CSI}J                             ## clear the screen
clear=$topleft$cls                      ## clear the screen and move to top left corner
clearEOL=${CSI}K                        ## clear from cursor to end of line
clearBOL=${CSI}1K                       ## clear from cursor to beginning of line
clearEOS=${CSI}0J                       ## clear from cursor to end of screen
clearBOS=${CSI}1J                       ## clear from cursor to beginning of screen


## Variable definitions for moving the cursor - (Listing 14-2c)
# cursor movement strings
     cu_up=${CSI}%sA
   cu_down=${CSI}%sB
  cu_right=${CSI}%sC
   cu_left=${CSI}%sD

# turn the cursor off and on
   cu_hide=${CSI}?25l
   cu_show=${CSI}?12l${CSI}?25h

# save the cursor position
   cu_save=${CSI}s                      ## or ${ESC}7

# move cursor to saved position
cu_restore=${CSI}u                      ## or ${ESC}8

# move cursor to next/previous line in block
     cu_NL=$cu_restore${cu_down/\%s/}$cu_save
     cu_PL=$cu_restore${cu_up/\%s/}$cu_save


## Variable definitions for colors and attributes - (Listing 14-2d)
# colors
  black=0
    red=1
  green=2
 yellow=3
   blue=4
magenta=5
   cyan=6
  white=7

     fg=3                               ## foreground prefix
     bg=4                               ## background prefix

# attributes
     bold=1
underline=4
  reverse=7

# set colors and attributes
  set_fg="${CSI}4%dm"                   ## set background color
  set_bg="${CSI}3%dm"                   ## set foreground color
set_fgbg="${CSI}3%d;4%dm"               ## set foreground and background colors
set_attr="${CSI}%dm"                    ## set attribute
