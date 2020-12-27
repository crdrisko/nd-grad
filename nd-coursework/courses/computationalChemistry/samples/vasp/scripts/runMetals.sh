#!/bin/bash
# Name: runMetals.sh - Version 1.0.0
# Author: Cody R. Drisko (crdrisko)
# Date: 11/21/2019-13:46:34
# Description:

if [ $1 = "Q2" ]
then
  for metal in Cu Ag Au
  do
    for dir in $metal/$metal-kpt-convergence/kpt-{3..11..2}
    do
  	  energyArray=( $(grep TOTEN $dir/OUTCAR | tail -n 1) )
	
	  if [ ${dir##*-} -ne 3 ]
	  then
	    lastEnergy=( $(grep $((${dir##*-} - 2)) $metal/energies.dat  | tail -n 1) )
	    echo ${dir##*-} ${energyArray[4]} $( echo "${lastEnergy[1]} - ${energyArray[4]}" | bc ) >> $metal/energies.dat
	  else
	    echo ${dir##*-} ${energyArray[4]} 0 > $metal/energies.dat
	  fi
    done
  done

  python3 runMetals.py Plot2

elif [ $1 = "Q3" ]
then
  for metal in Cu Ag Au
  do
    for dir in $metal/$metal-EOS/*
    do
      energyArray=( $(grep TOTEN $dir/OUTCAR | tail -n 1) ) 
      volumeArray=( $(grep volume $dir/OUTCAR | tail -n 1) )
      echo ${dir##*-} ${energyArray[4]} ${volumeArray[4]} >> $metal/$metal-EOS/energies.dat
    done
  done

  python3 runMetals.py Plot3 > EOS-Energies.dat
fi
