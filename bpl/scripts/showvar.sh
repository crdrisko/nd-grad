#!/bin/bash 
# Name: showvar.sh - (Listing 5-1)                                          
# Author: Cody R. Drisko (crdrisko)                       
# Date: 05/18/19-17:53:27                                 
# Description: Print value of variable x

if [ "${x+X}" = X ] ## if $x is set
then
  if [ -n "$x" ] ## if $x is not empty
  then
    printf " \$x = %s\n" "$x"
  else
    printf " \$x is set but empty\n"
  fi
else
  printf " %s is not set\n" "\$x"
fi


