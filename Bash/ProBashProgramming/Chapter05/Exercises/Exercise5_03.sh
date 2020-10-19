#!/bin/bash
# Copyright (c) 2019 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: Exercise5_03.sh
# Author: crdrisko
# Date: 06/30/2019-10:37:19
# Description: Extracts the second number in var=192.168.0.123

var=192.168.0.123
printf "%s\n" "${var:4:3}"
