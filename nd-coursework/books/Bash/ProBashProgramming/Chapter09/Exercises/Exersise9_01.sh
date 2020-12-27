#!/bin/bash
# Copyright (c) 2019 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: Exersise9_01.sh
# Author: crdrisko
# Date: 07/13/2019-12:40:40
# Description: Stores the time it takes a command to run

TIMEFORMAT='%3lR %3lU %3lS'
{ time echo {1..100000} >/dev/null 2>&1 ; } 2> sampleFile

read real user system < sampleFile
printf "%s\n" "$real" "$user" "$system"
rm sampleFile
