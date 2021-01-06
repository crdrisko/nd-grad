#!/bin/bash
# Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: format-codebase.sh - Version 1.0.0
# Author: crdrisko
# Date: 10/15/2020-07:20:58
# Description: Use clang-format on all files in the repository with the option to ignore specified files


### Functions ###
source errorHandling

printHelpMessage()      #@ DESCRIPTION: Print the format-code program's help message
{                       #@ USAGE: printHelpMessage
    printf "\nUSAGE: format-code [-hv] [-i fileName]\n\n"
    printf "  -h  Prints help information about the format-code program.\n"
    printf "  -v  Verbose mode. Defaults to false/off.\n\n"
    printf "  -i  OPTIONAL: Filename and path (relative to project root) to ignore\n"
    printf "        when formatting.\n\n"
    printf "EXAMPLE: format-code -i nd-research/src/applications/physicalQuantities.hpp -v\n\n"
}

formatFiles()           #@ DESCRIPTION: Use clang-format to format each file in the repository
{                       #@ USAGE: formatFiles ARRAY
    arr=("$@")

    for elem in "${arr[@]}"
    do
        if [[ -f "$elem" ]]
        then
            for file in "${ignoreFiles[@]}"
            do
                if [[ "$elem" == "$file" ]]
                then
                    continue 2;
                fi
            done

            printf "Formatting: %s\n" "$elem"
            /opt/local/libexec/llvm-10/bin/clang-format -i -style=file "$elem"

        else
            printFatalErrorMessage 2 "%s is not a valid file in the repository.\n" "$elem"
        fi
    done
}


### Initial Variables / Default Values ###
verbose=0
declare -a ignoreFiles headers samples tests

headers=( common-utilities/include/common-utils/errors/exceptions/fatalException.hpp
          common-utilities/include/common-utils/errors/exceptions/fileNotFoundException.hpp
          common-utilities/include/common-utils/errors/exceptions/invalidInputException.hpp
          common-utilities/include/common-utils/errors/traits/isFatal.hpp
          common-utilities/include/common-utils/errors/utils/errorHandling.hpp
          common-utilities/include/common-utils/errors/utils/errorTypes.hpp
          common-utilities/include/common-utils/errors.hpp
          common-utilities/include/common-utils/utilities/operators/comparisonOperators.hpp
          common-utilities/include/common-utils/utilities/utils/potentiallyEmptyBaseClass.hpp
          common-utilities/include/common-utils/utilities.hpp
          cpp-units/include/cpp-units/types/dimensionality.hpp
          cpp-units/include/cpp-units/types/physicalQuantity.hpp
          cpp-units/include/cpp-units/physicalQuantities.hpp )

samples=( common-utilities/libs/errors/samples/fibonacciExample.cpp
          common-utilities/libs/utilities/samples/comparableExample.cpp )

tests=( common-utilities/libs/errors/tests/testExceptions/testCommonExceptionTypes.hpp
        common-utilities/libs/errors/tests/testExceptions/testExceptionHandling.hpp
        common-utilities/libs/errors/tests/testTraits/testErrorTraits.hpp
        common-utilities/libs/errors/tests/testUtilities/testErrorHandling.hpp
        common-utilities/libs/errors/tests/testUtilities/testErrorTypes.hpp
        common-utilities/libs/errors/tests/testAllErrorFunctions.cpp
        common-utilities/libs/utilities/tests/testOperators/testComparisonOperators.hpp
        common-utilities/libs/utilities/tests/testUtilities/testPotentiallyEmptyBaseClass.hpp
        common-utilities/libs/utilities/tests/testAllUtilityFunctions.cpp
        cpp-units/libs/physicalQuantities/tests/testOperators/testArithmeticOperators.hpp
        cpp-units/libs/physicalQuantities/tests/testOperators/testComparisonOperators.hpp
        cpp-units/libs/physicalQuantities/tests/testOperators/testStreamOperators.hpp
        cpp-units/libs/physicalQuantities/tests/testTypes/testDimensionality.hpp
        cpp-units/libs/physicalQuantities/tests/testTypes/testPhysicalQuantity.hpp
        cpp-units/libs/physicalQuantities/tests/testAllPhysicalQuantityFunctions.cpp )


### Runtime Configuration ###
while getopts i:vh opt
do
    case $opt in
        i) ignoreFiles+=( "$OPTARG" ) ;;
        v) export verbose=1 ;;
        h) printHelpMessage && printFatalErrorMessage 0 ;;
        *) printFatalErrorMessage 1 "Invalid option flag passed to program." ;;
    esac
done


### Main Code ###
formatFiles "${headers[@]}"
formatFiles "${samples[@]}"
formatFiles "${tests[@]}"
