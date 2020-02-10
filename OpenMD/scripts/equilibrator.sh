#!/bin/bash
# Copyright (c) 2020 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for license information.
#
# Name: equilibrator.sh - Version 1.0.0
# Author: cdrisko
# Date: 02/07/2020-08:37:21
# Description: Standard equilibration procedure for an OpenMD simulation


### Functions ###
source errorHandling

printHelpMessage()      #@ DESCRIPTION: Print the equilibrator program's help message
{                       #@ USAGE: printHelpMessage
    printf "\nUSAGE: equilibrator [-hv] [-i fileName] [-o fileName] [-s submission] [-c cores]\n"
    printf "    [-t timing]\n\n"
    printf "  -h  Prints help information about the equilibrator program.\n"
    printf "  -v  Verbose mode. Defaults to false/off.\n\n"
    printf "  -i  REQUIRED: Pre-thermalized '.omd' input file.\n"
    printf "  -o  OPTIONAL: Output file for the end of the equilibration process.\n"
    printf "        Default is 'equil.eor'.\n"
    printf "  -s  OPTIONAL: Desired submission method, either queue or local. Default is\n"
    printf "        queue.\n"
    printf "  -c  OPTIONAL: The queuing system and number of cores required. Arguments\n"
    printf "        should be wrapped in quotes. Default is smp 16.\n"
    printf "  -t  OPTIONAL: Desired runTime selections, options are a positive integer.\n"
    printf "        When selected, the integer indicated corresponds to either the default\n"
    printf "        runTimes, or an integer multiple of the default runtimes. Default is 1.\n\n"
    printf "EXAMPLE: equilibrator -i NaClwarm.omd -s local -c \"mpi-24 24\"\n\n"
}

sciNotCalc()		#@ DESCRIPTION: Converts between scientific notation for simple calculations
{					#@ USAGE: sciNotCalc INT1 INT2 VAR
    product="$(( $1 * $2 ))"
    count=0

    while true
    do
        case $product in
            *'0') product=${product%?}
                  count=$(( count + 1 )) ;;
               *) break ;;
        esac
    done

    printf -v $3 "${product}e${count}"
}

spin()	    #@ DESCRIPTION: Print spinner until file exists
{		    #@ USAGE: spin FILENAME
    spinner="-\\|/-\\|/"

    while true
    do
        for i in {0..7}
        do
            echo -n "${spinner:$i:1}"
            echo -ne "\010"
            sleep 0.5
            [ -e ${1?} ] && echo && break 2
        done
    done
}

performRunType()        #@ DESCRIPTION: Run the calculations for a given part of the equilibration procedure
{                       #@ USAGE: performRunType RUNTYPE
    [ ${inputFileName:=$inputFile} ]
    currentEnsemble="$(grep ensemble $inputFileName)"
    currentTime="$(grep runTime $inputFileName)"

    case $1 in
        StructuralRelaxation) ## Structural Relaxation Parameters ##
                              desiredEnsemble="ensemble = NVT;"
                              desiredTime="runTime = ${strRelax};"
                              desiredFile=warm ;;

          PressureRelaxation) ## Pressure Relaxation Parameters ##
                              desiredEnsemble="ensemble = NPTi;"
                              desiredTime="runTime = ${presCorr};"
                              desiredFile=pres ;;

           ThermalRelaxation) ## Thermal Relaxation Parameters ##
                              desiredEnsemble="ensemble = NVT"
                              desiredTime="runTime = ${thermRelax};"
                              desiredFile=temp ;;

               Equilibration) ## Equilibration Parameters ##
                              desiredEnsemble="ensemble = NVE;"
                              desiredTime="runTime = ${equilibrate};"
                              desiredFile=equil ;;

                           *) printFatalErrorMessage 1 "$1 is not a valid runtype."
    esac

    cp $inputFileName $desiredFile.omd
    modifyFiles -i $desiredFile.omd -o "$currentEnsemble" -n "$desiredEnsemble"
    modifyFiles -i $desiredFile.omd -o "$currentTime" -n "$desiredTime"

    case $submission in
        queue) groupSubmit -i $desiredFile.omd -c "$cores"
               printf "Waiting for $1 to finish running ... " && spin $desiredFile.report ;;

        local) mpirun -np "${cores#*\ }" openmd_MPI $desiredFile.omd ;;

         test) testing=1 ;;

            *) printFatalErrorMessage 2 "Sorry, only 'queue' and 'local' are valid submission options." ;;
    esac

    inputFileName=$desiredFile.eor

    rm $desiredFile.dump
}


### Initial Variables / Default Values ###
submission=queue
cores=smp\ 16
timing=1
verbose=0


### Runtime Configuration ###
while getopts i:o:s:c:t:vh opt
do
    case $opt in
        i) inputFile=$OPTARG ;;
        o) outputFile=$OPTARG ;;
        s) submission=$OPTARG ;;
        c) cores="$OPTARG" ;;
        t) timing=$OPTARG ;;
        v) verbose=1 ;;
        h) printHelpMessage && printFatalErrorMessage 0 ;;
    esac
done


### Main Code ###
if ! [ -e ${inputFile:?An input file is required.} ]       	## Check existence of file
then
    printf -v fileErrorMessage "Sorry, we couldn't find %s here." "$inputFile"
    printFatalErrorMessage 3 "$fileErrorMessage"
fi

module load openmd &>/dev/null

## Calculation of desired runtimes ##
strRelax=
presCorr=
thermRelax=
equilibrate=

case $timing in
    *[!0-9]*) printFatalErrorMessage 4 "Timing option must be an integer." ;;
           *) sciNotCalc 10000 $timing strRelax                 ## 1e4 fs = 10 ps
              sciNotCalc 200000 $timing presCorr                ## 2e5 fs = 200 ps
              sciNotCalc 100000 $timing thermRelax              ## 1e5 fs = 100 ps
              sciNotCalc 1000000 $timing equilibrate ;;         ## 1e6 fs = 1000 ps = 1 ns
esac

## Structural Relaxation - NVT Ensemble ##
performRunType StructuralRelaxation

## Pressure Relaxation - NPTi Ensemble ##
performRunType PressureRelaxation

## AffineScale ##
volumeArray=( $(grep Volume pres.report) )
volume=${volumeArray[2]}
[ $testing -ne 1 ] && affineScale -m pres.eor -o temp.omd -v $volume
printf "Volume Used = %s\n" "$volume"

## Thermal Relaxation - NVT Ensemble ##
performRunType ThermalRelaxation

## Thermalize ##
energyArray=( $(grep Total\ Energy: temp.report) )
energy=${energyArray[3]}
[ $testing -ne 1 ] && thermalizer -i temp.omd -o equil.omd -e $energy
printf "Total Energy Used = %s\n" "$energy"

## Equilibration - NVE Ensemble ##
performRunType Equilibration

[ $outputFile ] && cp equil.eor $outputFile

printf "Equilibration process is now complete.\n"