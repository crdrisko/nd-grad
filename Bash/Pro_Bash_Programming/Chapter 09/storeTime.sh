#!/bin/bash
# Name: storeTime.sh - (Exersise 9-1)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/13/2019-12:40:40
# Description: Stores the time it takes a command to run

TIMEFORMAT='%3lR %3lU %3lS'
{ time echo {1..100000} >/dev/null 2>&1 ; } 2> sampleFile

read real user system < sampleFile
printf "%s\n" "$real" "$user" "$system"
rm sampleFile
