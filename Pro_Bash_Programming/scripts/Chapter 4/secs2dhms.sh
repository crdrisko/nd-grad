#!/bin/bash
# Name: secs2dhms.sh - (Listing 4-2)
# Author: Cody R. Drisko (crdrisko)
# Date: 06/29/2019-17:01:50
# Description: Convert seconds (in argument $1) to days, hours, minutes, and seconds

secs_in_day=86400
secs_in_hour=3600
mins_in_hour=60
secs_in_min=60

days=$(( $1 / $secs_in_day ))
secs=$(( $1 % $secs_in_day ))
printf "%d:%02d:%02d:%02d\n" "$days" "$(($secs / $secs_in_hour))" \
    "$((($secs / $mins_in_hour) % $mins_in_hour))" "$(($secs % $secs_in_min))"
