#!/bin/bash
# Name: valint.sh - (Listing 6-2)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/01/2019-12:17:15
# Description: Check for valid integer

valint()    #@ USAGE: valint INTEGER
    case ${1#-} in          ## Leading hyphen removed to accept negative numbers
        *[!0-9]*) false ;;  ## the string contains a non-digit character
        *) true ;;          ## the whole number, and nothing but the number
    esac

