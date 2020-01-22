#!/bin/bash
# Name: installND-Research.sh - Version 1.0.0
# Author: cdrisko
# Date: 01/08/2020-12:50:45
# Description: Installation of the Utilities-API library and shell scripts


if ! [ ${PWD##*/} = "install" ]
then
  printf "Must be in install directory to run installation.\n"
  exit 1
fi

cd ../../                           ## Go to the directory where ND-Research is located

if ! [ -d Utilites-API ]
then
  ## Install the required Utilities-API Repository ##
  git clone https://github.com/crdrisko/Utilites-API.git
  cd Utilites-API/install
  bash installUtilites-API.sh
fi

source repositoryInstallation 2> tempFile.err

if [ -f tempFile.err ]
then
  printf "Error with the installation of the Utilities-API repository. Refer to the\n\
    documentation at https://github.com/crdrisko/Utilities-API for installation\n\
    instructions and try again.\n"
  rm tempFile.err
  exit 2
fi

cd ../../ND-Research/install

## Use the functionality provided by the Utilities-API scripts ##
checkInstalDirectory                ## Verify user is in proper directory for installation
findScripts ../scripts              ## Find and make executable shell and python scripts in scripts directory
addPathToBashProfile                ## Add /usr/local/bin to user's bash profile if not already in $PATH

## Build the Programs in src Directory ##
# cd src

# for program in ChargedRNEMD RS-PES
# do
#   cd $program
#   printf "Compiling the %s program...\n" "$program"
#   bash build/Build${program}.sh
#   cd ../
# done

# cd ../install
