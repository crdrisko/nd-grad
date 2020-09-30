#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing15_05.sh
# Author: crdrisko
# Date: 08/11/2019-09:50:21
# Description: A simple record-editing script

record=root:x:0:0:root:/root:/bin/bash                  ## record to edit
fieldnames=( User Password UID
             GID Name Home Shell )

. key-funcs                                             ## Load the key functions

IFS=: read -a user <<EOF
$record
EOF                                                     ## read record into array

z=0
clear
while :                                                 ## loop until user presses 0 or q
do
  printf "\e[H\n
    0.     Quit
    1.     User: %s\e[K
    2. Password: %s\e[K
    3.      UID: %s\e[K
    4.      GID: %s\e[K
    5.     Name: %s\e[K
    6.     Home: %s\e[K
    7.    Shell: %s\e[K

     Select field (1-7): \e[0J" "${user[@]}"            ## print menu and prompt

  get_key field                                         ## get user input

  printf "\n\n"                                         ## print a blank line
  case $field in
    0|q|Q) break ;;                                     ## quit
    [1-7]) ;;                                           ## menu item selected; fall through
    *) continue ;;
  esac
  history -c                                            ## clear history
  history -s "${user[field-1]}"                         ## insert current value in history
  printf '  Press UP to edit "%s"\n' "${user[field-1]}" ## tell user what's there
  read -ep "        ${fieldnames[field-1]}: " val       ## get user entry
  case $val in
    *:*) echo "     Field may not contain a colon (press ENTER)" >&2    ## Error
         get_key; continue
         ;;
    "") continue ;;
    *) user[field-1]=$val ;;
  esac
done
