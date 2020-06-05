#!/bin/bash
# Copyright (c) 2020 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for license information.
#
# Name: saltWaterBoxer.sh - Version 1.1.1
# Author: cdrisko
# Date: 05/22/2020-11:15:28
# Description: Take an input packmol file and return a valid openmd file for a solution of salt water


### Functions ###
source errorHandling

printHelpMessage()      #@ DESCRIPTION: Print the saltWaterBoxer program's help message
{                       #@ USAGE: printHelpMessage
    printf "\nUSAGE: saltWaterBoxer [-hv] [-i inputFile] [-o outputFile]\n\n"
    printf "  -h  Prints help information about the saltWaterBoxer program.\n"
    printf "  -v  Verbose mode. Defaults to false/off.\n\n"
    printf "  -i  REQUIRED: The input packmol file which must create an xyz file.\n"
    printf "  -o  OPTIONAL: The name of the desired output omd file. Defaults to the input\n"
    printf "        file name.\n\n"
    printf "EXAMPLE: saltWaterBoxer -i saltWater.pack -v\n\n"
}

printMetaDataSection()      #@ DESCRIPTION: Print a sample OpenMD metaData section
{                           #@ USAGE: printMetaDataSection
    printf "\nensemble = NVT;\n"
    printf "forceField = \"SaltWater\";\n"
    printf "forceFieldFileName = \"SaltWater.frc\";\n"
    printf "electrostaticSummationMethod = \"shifted_force\";\n"
    printf "electrostaticScreeningMethod = \"damped\";\n"
    printf "cutoffRadius = 12;\n"
    printf "dampingAlpha = 0.18;\n"
    printf "seed = 8675309;\n\n"
    printf "targetTemp = 300;\n"
    printf "targetPressure = 1.0;\n\n"
    printf "tauThermostat = 1e3;\n"
    printf "tauBarostat = 1e4;\n\n"
    printf "dt = 2.0;\n"
    printf "runTime = 1e3;\n\n"
    printf "sampleTime = 100;\n"
    printf "statusTime = 2;\n\n"
}


### Initial Variables / Default Values ###
verbose=0
directory="$PWD"


### Runtime Configuration ###
while getopts i:o:vh opt
do
    case $opt in
        i) inputFile="${OPTARG##*/}"
           if [[ "$inputFile" != "${OPTARG%/*}" ]]
           then
               directory="${OPTARG%/*}"
           fi ;;
        o) outputFile="$OPTARG" ;;
        v) verbose=1 ;;
        h) printHelpMessage && printFatalErrorMessage 0 ;;
    esac
done


### Main Code ###
[ -d "$directory" ] && cd "$directory" || printFatalErrorMessage 1 "Invalid directory."

xyzFileArray=( $( grep output $inputFile ) )
xyzFileName=${xyzFileArray[1]}

packmol < $inputFile

## Take the MetaData through FrameData sections of the omd file generated by atom2omd ##
atom2omd -ixyz $xyzFileName -oomd ${xyzFileName%%.*}.omd

metaDataLineNumber="$( grep -n \<\/MetaData\> ${xyzFileName%%.*}.omd )"
head -n $(( ${metaDataLineNumber%%:*} - 1 )) ${xyzFileName%%.*}.omd > tempFile

printMetaDataSection >> tempFile

frameDataLineNumber="$( grep -n \<\/FrameData\> ${xyzFileName%%.*}.omd )"
head -n "${frameDataLineNumber%%:*}" ${xyzFileName%%.*}.omd | tail -n +${metaDataLineNumber%%:*} >> tempFile

# Take the StuntDouble section of the omd file generated by waterReplacer ##
waterReplacer -x $xyzFileName -o ${xyzFileName%%.*}2.omd

sed '/<StuntDoubles>/,$!d' ${xyzFileName%%.*}2.omd >> tempFile

rm ${xyzFileName%%.*}2.omd
mv tempFile ${outputFile:=${inputFile%%.*}.omd}

## Account for periodic boundary conditions unaccounted for by packmol ##
toleranceArray=( $( grep tolerance $inputFile ) )
tolerance=${toleranceArray[1]}

hmatArray=( $( grep Hmat $outputFile ) )
Hxx=${hmatArray[2]}
Hyy=${hmatArray[8]}
Hzz=${hmatArray[14]}

oldHmat="Hmat: {{ $Hxx 0, 0 }, { 0, $Hyy 0 }, { 0, 0, $Hzz }}"

Hxx=$( echo "${Hxx%,*} + (0.5 * $tolerance)" | bc )
Hyy=$( echo "${Hyy%,*} + (0.5 * $tolerance)" | bc )
Hzz=$( echo "${Hzz%,*} + (0.5 * $tolerance)" | bc )

newHmat="Hmat: {{ $Hxx, 0, 0 }, { 0, $Hyy, 0 }, { 0, 0, $Hzz }}"

modifyFiles -i $outputFile -o "$oldHmat" -n "$newHmat" -f
