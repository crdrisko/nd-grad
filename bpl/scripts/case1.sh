#!/bin/bash
# Title: case1 - (Listing 3-4)
# Author: Cody R. Drisko (crdrisko)
# Date: 5/12/2019
# Description: Does one string contain another?

case $1 in
  *"$2"*) true ;;
  *) false ;;
esac

