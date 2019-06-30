#!/bin/bash
# Name: validInt.sh - (Listing 3-5)
# Author: Cody R. Drisko (crdrisko)
# Date: 06/29/2019-13:36:35
# Description: Is this a valid integer?

case $1 in
    *[!0-9]*) false ;;
    *) true ;;
esac
