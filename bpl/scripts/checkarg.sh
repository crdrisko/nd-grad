#!/bin/bash 
# Name: checkarg.sh - (Listing 5-2)                                          
# Author: Cody R. Drisko (crdrisko)                       
# Date: 05/18/19-18:22:55                                 
# Description: Exit if parameters are unset of empty                                           

## Check for unset arguments
: ${1?An argument is required} \
  ${2?Two arguments are required}

## Check for empty arguments
: ${1:?A non-empty argument is required} \
  ${2:?Two non-empty arguments are required}

echo "Thank you."
