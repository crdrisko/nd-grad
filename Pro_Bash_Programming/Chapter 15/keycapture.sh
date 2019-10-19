#!/bin/bash
# Name: keycapture.sh - (Listing 15-3)
# Author: Cody R. Drisko (crdrisko)
# Date: 08/10/2019-09:31:02
# Description: Read and display keystrokes until Q is pressed

. key-funcs.sh                              ## source the library
while :                                     ## infinite loop
do
  get_key key
  sa "$key"                                 ## the sa command is from previous chapters
  case $key in q|Q) break ;; esac
done
