#!/bin/bash
# Copyright (c) 2020 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for license information.
#
# Name: runAllTests.sh - Version 1.0.0
# Author: cdrisko
# Date: 02/06/2020-07:46:14
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
  compiler ${additionalFiles[@]} -o test${1}.out -l gtest -l utilities-api -r

  unset additionalFiles
}

cd TestFluxTypes/FluxType_Current
compileAndRunTests CurrentRNEMD\
    "../../../rnemd/RNEMDFileParsing/src/rnemdFile ../../../rnemd/RNEMDFileParsing/src/rnemdRegion"

cd ../FluxType_KE
compileAndRunTests KE_RNEMD\
    "../../../rnemd/RNEMDFileParsing/src/rnemdFile ../../../rnemd/RNEMDFileParsing/src/rnemdRegion"

cd ../FluxType_Px
compileAndRunTests Px_RNEMD\
    "../../../rnemd/RNEMDFileParsing/src/rnemdFile ../../../rnemd/RNEMDFileParsing/src/rnemdRegion"

cd ../FluxType_Single
compileAndRunTests SingleRNEMD\
    "../../../rnemd/RNEMDFileParsing/src/rnemdFile ../../../rnemd/RNEMDFileParsing/src/rnemdRegion"

cd ../../TestChargedRNEMD
compileAndRunTests ChargedRNEMDParameters\
    "../../rnemd/RNEMDFileParsing/src/rnemdFile ../../rnemd/RNEMDFileParsing/src/rnemdRegion"
