#!/bin/bash
# Name: runLab4.sh - Version 1.0.0
# Author: Cody R. Drisko (crdrisko)
# Date: 11/20/2019-21:42:01
# Description:

for dir in EOS/Pd*
do
  energyArray=( $(grep TOTEN $dir/OUTCAR | tail -n 1) ) 
  volumeArray=( $(grep volume $dir/OUTCAR | tail -n 1) )
  echo ${dir##*-} ${energyArray[4]} ${volumeArray[4]} >> energies.dat
done

python3 Lab4_1.py Plot
