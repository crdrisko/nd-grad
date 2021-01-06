#!/bin/bash
# Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: afsInit.sh - Version 1.1.1
# Author: cdrisko
# Date: 07/20/2020-08:00:43
# Description: Initialize the connection to the afs servers for the supplied username


### Functions ###
source errorHandling
source typeParsing

printHelpMessage()      #@ DESCRIPTION: Print the afsInit program's help message
{                       #@ USAGE: printHelpMessage
    printf "\nUSAGE: afsInit [-hv] [-u STRING] [-t INT]\n\n"
    printf "  -h  Prints help information about the afsInit program.\n"
    printf "  -v  Verbose mode. Defaults to false/off.\n\n"
    printf "  -u  REQUIRED: CRC username for access to the afs servers.\n"
    printf "  -t  OPTIONAL: How long (in seconds) to give CISCO to verify a VPN connection.\n"
    printf "        Defaults to ~15 seconds.\n\n"
    printf "EXAMPLE: afsInit -u cdrisko -t 30 -v\n\n"
}

spin()                  #@ DESCRIPTION: Print spinner until time is exceeded
{                       #@ USAGE: spin TIME
    spinner="-\\|/-\\|/"

    echo -n "Connecting..."

    for ((i = 0; i < $1/4; i++))
    do
        for j in {0..7}
        do
            echo -n "${spinner:$j:1}"
            echo -ne "\010"
            sleep 0.5
        done
    done

    echo
}

connectToCampusVPN()    #@ DESCRIPTION: Make the connection to campus VPN via Cisco
{                       #@ USAGE: connectToVPN TIME
    if [[ $OSTYPE == darwin* && ! $( pgrep Cisco | wc -l ) -ge 1 ]]
    then
        ## We'll go ahead and make the connection to Cisco for you, careful not to take too long though ##
        if open -a "Cisco AnyConnect Secure Mobility Client" 2>/dev/null
        then
            spin "$1"
        fi
    fi
}


### Initial Variables / Default Values ###
declare verbose userName timing

verbose=0
timing=15


### Runtime Configuration ###
while getopts u:t:vh opt
do
    case $opt in
        u) STRING userName = "$OPTARG" ;;
        t) INT    timing   = "$OPTARG" ;;
        v) export verbose=1 ;;
        h) printHelpMessage && printFatalErrorMessage 0 ;;
        *) printFatalErrorMessage 1 "Invalid option flag passed to program." ;;
    esac
done


### Main Code ###
set -e

[[ ${userName:?A username is required} ]]

connectToCampusVPN "$timing"

if [[ $( tokens | wc -l ) -le 4 ]]
then
    kinit -l 30d "$userName"@CRC.ND.EDU                     ## Initialize the tokens for the CRC's cell on afs
    aklog                                                   ## Obtain token for authentication with afs servers
    tokens                                                  ## List the tokens to verify success of the authentication
fi
