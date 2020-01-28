#!/bin/bash
# Name: runAllTests.sh - Version 1.0.1
# Author: cdrisko
# Date: 01/10/2020-12:22:40
# Description: Compiles and runs all unit tests in the test directory


### Functions ###
compileAndRunTests()    #@ DESCRIPTION: Compile and run the test scripts using the googletest API
{                       #@ USAGE: compileAndRunTests STRING [ADDITIONAL_FILES]
  for file in $2
  do
    additionalFiles+=( "-i $file.cpp" )
  done

  yes | remover -e -w txt &>/dev/null

  printf "\nPreparing %s tests...\n" "$1"
  compiler ${additionalFiles[@]} -o test${1}.out -l gtest -l utilities_api -r

  unset additionalFiles
}

cd TestFluxTypes/FluxType_Current
compileAndRunTests CurrentRNEMD "../../../src/OpenMD/src/rnemdFile ../../../src/OpenMD/src/rnemdRegion"

cd ../FluxType_KE
compileAndRunTests KE_RNEMD "../../../src/OpenMD/src/rnemdFile ../../../src/OpenMD/src/rnemdRegion"

cd ../FluxType_Px
compileAndRunTests Px_RNEMD "../../../src/OpenMD/src/rnemdFile ../../../src/OpenMD/src/rnemdRegion"

cd ../FluxType_Single
compileAndRunTests SingleRNEMD "../../../src/OpenMD/src/rnemdFile ../../../src/OpenMD/src/rnemdRegion"

cd ../../TestChargedRNEMD
compileAndRunTests ChargedRNEMDParameters "../../src/OpenMD/src/rnemdFile ../../src/OpenMD/src/rnemdRegion"
