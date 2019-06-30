#!/bin/bash
# Name: checkarg.sh - (Listing 5-2)
# Author: Cody R. Drisko (crdrisko)
# Date: 06/30/2019-09:52:43
# Description: Exit if parameters are unset or empty

## Check for unset arguments
: ${1?An argument is required} \
  ${2?Two arguments are required}

## Check for empty arguments
: ${1:?A non-empty argument is required} \
  ${2:?Two non-empty arguments are required}

echo "Thank you."
