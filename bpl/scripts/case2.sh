#!/bin/bash
# Title: case2 - (Listing 3-5)
# Author: Cody R. Drisko (crdrisko)
# Date: 5/12/2019
# Description: Is this a valid integer?

case $1 in
  *[!0-9]*) false ;;
  *) true ;;
esac

