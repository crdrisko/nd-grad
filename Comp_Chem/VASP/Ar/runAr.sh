#!/bin/bash
# Name: runAr.sh - Version 1.0.0
# Author: Cody R. Drisko (crdrisko)
# Date: 11/07/2019-18:52:17
# Description:


## Question 1 ##
python runAr.py Q1
 
while true
do
  [ -f molecules/simple-ar/OUTCAR ] && break
done

sleep 5 ## bash seems to jump the gun, so let the job finish before analysis

for selection in NELECT TOTEN Iteration NPLWV
do
  echo "$selection:"
  grep $selection molecules/simple-ar/OUTCAR | tail -n 1
  echo
done



## Question 2 ##
for cutoff in 100 200 300 400 500
do
  python runAr.py $cutoff

  while true
  do
    [ -f molecules/cutoff-ar-$cutoff/OUTCAR ] && break
  done
  
  sleep 5 ## bash seems to jump the gun, so let the job finish before analysis

  energyArray=( $(grep TOTEN molecules/cutoff-ar-$cutoff/OUTCAR | tail -n 1) )
  timeArray=( $(grep Elapsed molecules/cutoff-ar-$cutoff/OUTCAR | tail -n 1) )
  echo "$cutoff ${energyArray[4]} ${timeArray[3]}" >> energies.dat
done

python runAr.py Plot

