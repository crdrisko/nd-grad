#!/bin/bash
# Name: runGAMESS.sh - Version 1.0
# Author: Cody R. Drisko (crdrisko)
# Date: 09/29/2019-08:45:51
# Description: Submit GAMESS jobs to the CRC queue


modifyFiles()		#@ DESCRIPTION: Modify a file using sed
{					#@ USAGE: modifyFiles fileName oldString newString
  sed "s/${2?}/${3?}/g" ${1?} > tempFile && mv tempFile ${1?}
}


lengths=(1.30 1.35 1.40 1.45 1.50 1.55 1.60 1.65 1.70 1.75)
angles=(90 95 100 105 110 115 120 125 130 135 140 145 150)


for len in ${lengths[@]}
do
  mkdir ${len}-A
  cd ${len}-A

  for ang in ${angles[@]}
  do
	mkdir ${ang}-deg
	cd ${ang}-deg

	cp ../../SO2_temp.inp SO2.inp

	modifyFiles SO2.inp LEN $len
	modifyFiles SO2.inp ANG $ang

	rungms SO2.inp > SO2.out

	energyArray=( $(grep FINAL\ R-PBE\ ENERGY\ IS SO2.out) )
	energy=${energyArray[4]}

	printf "%s\t %s\t %s\n" $len $ang $energy >> ../../allEnergies.dat

	cd ../
  done
  cd ../
done
