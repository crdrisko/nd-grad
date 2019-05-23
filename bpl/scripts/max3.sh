#!/bin/bash 
# Name: max3.sh - (Listing 6-5)                                           
# Author: Cody R. Drisko (crdrisko)                       
# Date: 05/23/19-11:26:03                                 
# Description: Sort three integers

_max3() { #@ Sort 3 integers and store in $_MAX3, $_MID3, and $_MIN3
  [ $# -ne 3 ] && return 5
  [ $1 -gt $2 ] && { set -- $2 $1 $3; }
  [ $2 -gt $3 ] && { set -- $1 $3 $2; }
  [ $1 -gt $2 ] && { set -- $2 $1 $3; }
  _MAX3=$3
  _MID3=$2
  _MIN3=$1
}

