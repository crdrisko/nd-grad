#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing15_02.sh
# Author: crdrisko
# Date: 08/10/2019-08:37:45
# Description: A menu that responds to a single keypress

. key-funcs.sh

while :
do
  printf "\n\n\t$bar\n"
  printf "\t %d. %s\n" 1 "Do something" \
                       2 "Do something else" \
                       3 "Quit"
  printf "\t%s\n" "$bar"
  _key
  case $_KEY in
    1) printf "\n%s\n\n" "Something" ;;
    2) printf "\n%s\n\n" "Something else" ;;
    3) break ;;
    *) printf "\a\n%s\n\n" "Invalid choice; try again"
       continue
       ;;
  esac
  printf ">>> %s " "Press any key to continue"
  _key
done
