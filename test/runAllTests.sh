#!/bin/bash
# Name: runAllTests.sh - Version 1.0.0
# Author: cdrisko
# Date: 01/10/2020-12:22:40
# Description: Compiles and runs all unit tests in the test directory


### Functions ###
compileAndRunTests()    #@ DESCRIPTION: Compile and run the test scripts using the googletest API
{                       #@ USAGE: compileAndRunTests STRING [ADDITIONAL_FILES]
  for file in $2
  do
    additionalFiles+=( "-i $file" )
  done

  printf "\nPreparing %s tests...\n" "$1"
  compiler ${additionalFiles[@]} -o test${1}.out -l gtest -l utilities_api-static

  unset additionalFiles
}

cd TestFluxTypes/FluxType_Current
compileAndRunTests CurrentRNEMD "../../../src/OpenMD/src/rnemdFile.cpp ../../../src/OpenMD/src/rnemdRegion.cpp"

cd ../FluxType_Single
compileAndRunTests SingleRNEMD "../../../src/OpenMD/src/rnemdFile.cpp ../../../src/OpenMD/src/rnemdRegion.cpp"
