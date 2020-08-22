#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: containString.sh - (Listing 3-4)
# Author: Cody R. Drisko (crdrisko)
# Date: 06/29/2019-13:33:39
# Description: Does one string contain another?

case $1 in
    *"$2"*) true ;;
    *) false ;;
esac
