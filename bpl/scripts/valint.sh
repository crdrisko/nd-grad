#!/bin/bash 
# Name: valint.sh - (Listing 6-2)                                          
# Author: Cody R. Drisko (crdrisko)                       
# Date: 05/23/19-10:43:36                                 
# Description: Check for valid integer                                           
valint() #@ USAGE: valint INTEGER
  case ${1#-} in 	## Leading hyphen remobed to accept negative numbers
    *[!0-9]*) false;; 	## The sting contains a non-digit character
    *) true ;; 		## The whole number, and nothing but the number
  esac


