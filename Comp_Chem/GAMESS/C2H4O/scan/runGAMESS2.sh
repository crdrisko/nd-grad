#!/bin/bash
# Name: runGAMESS2.sh - Version 1.0.0
# Author: Cody R. Drisko (crdrisko)
# Date: 10/17/2019-11:34:28
# Description: Submit GAMESS jobs to the CRC queue

modifyFiles()		#@ DESCRIPTION: Modify a file using sed
{			#@ USAGE: modifyFiles fileName oldString newString
  sed "s/${2?}/${3?}/g" ${1?} > tempFile && mv tempFile ${1?}
}

angles=(0 10 20 30 40 50 60 70 80 90 100 110 120 130 140 150 160 170 180)

for ang in ${angles[@]}
do
  mkdir ${ang}-deg
  cd ${ang}-deg

  cp ../acetaldehyde_scan.inp acetaldehyde.inp

  modifyFiles acetaldehyde.inp ANG $ang

  rungms acetaldehyde.inp > acetaldehyde.out

  energyArray=( $(grep FINAL\ R-B3LYP\ ENERGY\ IS acetaldehyde.out) )
  energy=${energyArray[4]}

  printf "%s\t %s\n" $ang $energy >> ../allEnergies.dat

  cd ../
done

