#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing12_10.sh
# Author: crdrisko
# Date: 07/22/2019-08:42:16
# Description: Archive and upload files to remote computer

### Script Information ###
scriptname=${0##*/}
description="Archive new or modified files and upload to web site"
author="Chris F.A. Johnson"
version=1.0
copyright=2009

### Default Configuration ###
## Default values and settings array - (Listing 12-10a)
# archive and upload settings
host=127.0.0.1                          ## Remote host (URL or IP address)
port=22                                 ## SSH port
dest=work/upload                        ## Destination directory
user=chris                              ## Login name on remote system
source=$HOME/public_html/example.com    ## Local directory to upload
archivedir=$HOME/work/webarchives       ## Directory to store archive files
syncfile=.sync                          ## File to touch with time of last upload

# array containing variables and their descriptions
varinfo=( "" ## Empty element to emulate 1-based array
    "host:Remote host (URL or IP address)"
    "port:SSH port"
    "dest:Destination directory"
    "user:Login name on remote system"
    "source:Local directory to upload"
    "archivedir:Directory to store archive files"
    "syncfile:File to touch with time of last upload"
)

# these may be changed by command-line options
menu=0                                  ## do not print a menu
qa=0                                    ## do not use question and answer
test=0                                  ## 0=upload for real; 1=don't archive/upload, show settings
configfile=                             ## if defined, the file will be sourced
configdir=$HOME/.configdir              ## default location for configuration files
sleepytime=2                            ## delay in seconds after printing messages

# bar to print across the top and bottom of menu (and possibly elsewhere)
bar=================================================================
bar=$bar$bar$bar$bar                    ## make long enough for any terminal window
menuwidth=${COLUMNS:-80}


### Screen Configuration ###
## Define screen manipulation variables - (Listing 12-10b)
topleft='\e[0;0H'                       ## Move cursor to top left corner of screen
clearEOS='\e[J'                         ## Clear from cursor position to end of screen
clearEOL='\e[K'                         ## Clear from cursor position to end of line


### Function Definitions ###
## Define die function - (Listing 12-10c)
die()           #@ Print error message and exit with error code
{               #@ USAGE: die [errno [message]]
    error=${1:-1}                       ## exits with 1 if error number not given
    shift
    [ -n "$*" ] &&
        printf "%s%s: %s\n" "$scriptname" ${version:+" ($version)"} "$*" >&2
    exit "$error"
}

## Define menu function - (Listing 12-10d)
menu()          #@ Print menu, and change settings according to user input
{
    local max=$#
    local menutitle="UPLOAD SETTINGS"
    local readopt

    if [ $max -lt 10 ]
    then                                ## if fewer than 10 items,
        readopt=-sn1                    ## allow single key entry
    else
        readopt=
    fi

    printf "$topleft$clearEOS"          ## Move cursor to top left and clear screen

    while :                             ## Infinite loop
    do
        ###############################################################################
        # display menu
        #
        printf "$topleft"               ## Move cursor to top left corner of screen

        # print menu title between horizontal bars the width of the screen
        printf "\n%s\n" "${bar:0:$menuwidth}"
        printf "    %s\n" "$menutitle"
        printf "\n%s\n" "${bar:0:$menuwidth}"

        menunum=1

        # loop through the positional parameters
        for item
        do
            var=${item%%:*}             ## variable name
            description=${item#*:}      ## variable description

            # print item number, description, and value
            printf "   %${#max}d: %s (%s)$clearEOL\n" \
                       "$menunum" "$description" "${!var}"

            menunum=$(( $menunum + 1 ))
        done

        # ... and menu adds its own items
        printf "    %${##}s\n" "q: Quit menu, start uploading" \
                            "0: Exit $scriptname"

        printf "\n${bar:0:$menuwidth}\n"    ## Closing bar

        printf "$clearEOS\n"            ## Clear to end of screen
        #
        ###############################################################################

        ###############################################################################
        # user selection and parameter input
        #

        read -p "Select 1..$max or 'q' " $readopt x
        echo
        [ "$x" = q ] && break           ## User selected quit
        [ "$x" = 0 ] && exit            ## User selected Exit

        case $x in
            *[!0-9]* | "")
                    # contains non digit or is empty
                    printf "\a %s - Invalid entry\n" "$x" >&2
                    sleep "$sleepytime"
                    ;;
            *)  if [ $x -gt $max ]
                then
                    printf "\a %s - Invalid entry\n" "$x" >&2
                    sleep "$sleepytime"
                    continue
                fi

                var=${!x%%:*}
                description=${!x#*:}

                # prompt user for new value
                printf "      %s$clearEOL\n" "$description"
                readline value "        >> " "${!var}"

                # if user did not enter anything, keep old value
                if [ -n "$value" ]
                then
                    eval "$var=\$value"
                else
                    printf "\a Not changed\n" >&2
                    sleep "$sleepytime"
                fi
                ;;
        esac
        #
        ###############################################################################
    done
}

## Define qa function - (Listing 12-10e)
qa()            #@ Question and answer dialog for variable entry
{
    printf "\n %s - %s\n" "$scriptname" "$description"
    printf " by %s, copyright %d\n" "$author" "$copyright"
    echo
    if [ ${BASH_VERSINFO[0]} -ge 4 ]
    then
        printf "%s\n" "You may edit existing value using the arrow keys."
    else
        printf "%s\n" "Press the up arrow to bring existing value" \
                      "to the cursor for editing with the arrow keys"
    fi
    echo

    local item var description
    for item
    do
        # split $item into variable name and description
        var=${item%%:*}
        description=${item#*:}
        printf "\n %s\n" "$description"
        readline value "   >> " "${!var}"
        [ -n "$value" ] && eval "$var=\$value"
    done

    menu "$@"
}

## Define print_config function - (Listing 12-10f)
print_config()  #@ Print values in a format suitable for a configuration file
{
    local item var description

    [ -t 1 ] && echo                    ## print blank line if output is to a terminal

    for item in "${varinfo[@]}"
    do
        var=${item%%:*}
        description=${item#*:}
        printf "%-35s ## %s\n" "$var=\"${!var//\"/\\\"}\"" "$description"
    done

    [ -t 1 ] && echo                    ## print blank line if output is to a terminal
}

## Define readline function - (Listing 12-10g)
readline()      #@ get line from user with editing of current value
{               #@ USAGE: var [prompt] [default]
    local var=${1?} prompt=${2:- >>> } default=$3

    if [${BASH_VERSINFO[0]} -gt 4 ]
    then
        read -ep "$prompt" ${default:+-i "$default"} "$var"
    else
        history -s "$default"
        read -ep "$prompt" "$var"
    fi
}


### Parse Command-Line Options ###
## Parse command-line options - (Listing 12-10h)
while getopts c:h:p:s:d:u:a:f:mqt var
do
    case "$var" in
        c) configfile=$OPTARG ;;
        h) host=$OPTARG
           hostconfig=$configdir/$scriptname.$host.cfj
           [ -f "$hostconfig" ] &&
            configfile=$hostconfig ;;
        p) port=$OPTARG ;;
        s) source=$OPTARG ;;
        d) dest=$OPTARG ;;
        u) user=$OPTARG ;;
        a) archivedir=$OPTARG ;;
        f) syncfile=$OPTARG ;;
        m) menu=1 ;;                    ## show configuration, but do not archive or upload
        t) test=1 ;;
        q) qa=1 ;;
    esac
done
shift $(( $OPTIND - 1 ))


### Bits and Pieces ###
## The rest of the script - (Listing 12-10i)
# if a configuration file is defined, try to load it
if [ -n "$configfile" ]
then
    if [ -f "$configfile" ]
    then
        # exit if problem with config file
        . "$configfile" || die 1 "Configuration error"
    else
        # exit if configuration file is not found
        die 2 "Configuration file, $configfile, not found"
    fi
fi

# execute menu or qa if defined
if [ $menu -eq 1 ]
then
    menu "${varinfo[@]}"
elif [ $qa -eq 1 ]
then
    qa "${varinfo[@]}"
fi

# create datestamped filename for tarball
tarfile=$archivedir/$host.$(date +%Y-%m-%dT%H:%M:%S.tgz)

if [ $test -eq 0 ]
then
    cd "$source" || die 4
fi

# verbose must be set (or not) in the environment or on the command line
if [ ${verbose:-0} -gt 0 ]
then
    printf "\nArchiving and uploading new files in directory: %s\n\n" "$PWD"
    opt=v
else
    opt=
fi

# IFS=$'\n'         # uncomment this line if you have spaces in filenames (shame on you!)
if [ ${test:-0} -eq 0 ]
then
    remote_command="cd \"$dest\" || exit;tar -xpzf -"
    # archive files newer than $syncfile
    tar cz${opt}f "$tarfile" $( find . -type f -newer "$syncfile" ) &&
        # execute tar on remote computer with input from $tarfile
        ssh -p "$port" -l "$user" "$host" "$remote_command" < $"tarfile" &&
            # if ssh is successful
            touch "$syncfile"
else                                    ## Test mode
    print_config
fi
