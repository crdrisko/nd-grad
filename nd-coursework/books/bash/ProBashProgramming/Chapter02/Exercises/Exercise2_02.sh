#!/bin/bash
# Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: Exercise2_02.sh
# Author: crdrisko
# Date: 06/29/2019-09:40:44
# Description: Prints 8 random numbers to both a file and a variable

printf -v var "%5s.%-5s\n" "$RANDOM" "$RANDOM" "$RANDOM" "$RANDOM"  \
    "$RANDOM" "$RANDOM" "$RANDOM" "$RANDOM"
printf "%s" "$var" | tee randomFile
