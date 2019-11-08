#!/bin/bash
# Name: runO.sh - Version 1.0.0
# Author: Cody R. Drisko (crdrisko)
# Date: 11/07/2019-21:31:57
# Description:

python runO.py
 
while true
do
  [ -f molecules/simple-o/OUTCAR ] && break
done

sleep 5 ## bash seems to jump the gun, so let the job finish before analysis

for selection in NELECT TOTEN Iteration NPLWV
do
  echo $selection:
  grep $selection molecules/simple-o/OUTCAR | tail -n 1
  echo
done

