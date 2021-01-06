#!/bin/bash
# Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: groupSubmit.sh - Version 1.3.1
# Author: cdrisko
# Date: 01/20/2020-10:22:05
# Description: Gezelter group submission script creator and resource monitor


### Functions ###
source errorHandling
source typeParsing

printHelpMessage()              #@ DESCRIPTION: Print the groupSubmit program's help message
{                               #@ USAGE: printHelpMessage
    printf "\nUSAGE: groupSubmit [-hvd] [-i FILE] [-s FILE] [-u STRING] [-c STRING]\n\n"
    printf "  -h  Prints help information about the groupSubmit program.\n"
    printf "  -v  Verbose mode. Defaults to false/off.\n"
    printf "  -d  Submit jobs to the debug queue. Defaults to false/off.\n\n"
    printf "  -i  OPTIONAL: Your input '.omd' file to be submitted. Note that this is\n"
    printf "        required if no submission script is provided via the '-s' option.\n"
    printf "  -s  OPTIONAL: Specify an alternative submission script to be submited to\n"
    printf "        the CRC queue. Defaults to openmd_multiple.sh.\n"
    printf "  -u  OPTIONAL: Your ND email username. Defaults to your CRC username and\n"
    printf "        should only be set if the two are different.\n"
    printf "  -c  OPTIONAL: The queuing system and number of cores required. Arguments\n"
    printf "        should be wrapped in quotes. Defaults to \"smp 16\".\n\n"
    printf "EXAMPLE: groupSubmit -i testFile.omd -c \"mpi-24 24\"\n\n"
}

printCheckQuotaScript()         #@ DESCRIPTION: Print script used to notify user of potential memory overflow
{                               #@ USAGE: printCheckQuotaScript [User|Group]
    printf "#!/bin/bash\n"
    printf "#$ -N check%sQuota\n" "$1"
    printf "#$ -M %s@nd.edu\n" "$username"
    printf "#$ -m abe\n"
    printf "#$ -pe smp 1\n\n"
    printf "while true\n"
    printf "do\n"
    printf "    quotaArray=( \$( /usr/bin/fs quota ) )\n"
    printf "    quotaPercentage=\${quotaArray[0]}\n"
    printf "    quotaPercentage=\${quotaPercentage%%%%\\%%*}\n\n"
    printf "    if [ \$quotaPercentage -ge 99 ]\n"
    printf "    then\n"
    printf "        ## Send DANGER if within 1%% of available quota ##\n"
    printf "        mail -s 'DANGER' %s@nd.edu <<< 'You have used 99%% of your available quota.'\n" "$username"
    printf "        sleepTime=15m\n\n"
    printf "    elif [ \$quotaPercentage -ge 95 ]\n"
    printf "    then\n"
    printf "        ## Send WARNING if within 5%% of available quota ##\n"
    printf "        mail -s 'WARNING' %s@nd.edu <<< 'You have used 95%% of your available quota.'\n" "$username"
    printf "        sleepTime=30m\n\n"
    printf "    elif [ \$quotaPercentage -ge 90 ]\n"
    printf "    then\n"
    printf "        ## Send CAUTION if within 10%% of available quota ##\n"
    printf "        mail -s 'CAUTION' %s@nd.edu <<< 'You have used 90%% of your available quota.'\n" "$username"
    printf "        sleepTime=1h\n"
    printf "    fi\n\n"
    printf "    ## Put machine to sleep before next check ##\n"
    printf "    sleep \${sleepTime:=2h}\n\n"
    printf "    qstatArray=( \$( /opt/sge/bin/lx-amd64/qstat -u %s | tail -n +3 ) )\n" "$USER"
    printf "    qstatArrayLength=\$( printf \"%%s\\\n\" \${qstatArray[@]} | wc -l )\n\n"
    printf "    case \$qstatArrayLength in\n"
    printf "         9) ## Only one filesystem is being checked ##\n"
    printf "            if [[ \${qstatArray[2]} == \"checkUserQ\" || \${qstatArray[2]} == \"checkGroup\" ]]\n"
    printf "            then\n"
    printf "                exit 0\n"
    printf "            fi ;;\n"
    printf "        18) ## Only one filesystem is being checked ##\n"
    printf "            if [[ \${qstatArray[2]} == \"checkUserQ\" && \${qstatArray[11]} == \"checkGroup\" ]]\\\\\n"
    printf "                || [[ \${qstatArray[11]} == \"checkUserQ\" && \${qstatArray[2]} == \"checkGroup\" ]]\n"
    printf "            then\n"
    printf "                exit 0\n"
    printf "            fi ;;\n"
    printf "    esac\n"
    printf "done\n\n"
}

printOpenmdSubmissionScript()   #@ DESCRIPTION: Print script used to run the OpenMD job
{                               #@ USAGE: printOpenmdSubmissionScript
    printf "#!/bin/bash\n"
    printf "#$ -N %s\n" "${inputFile%%.*}"
    printf "#$ -M %s@nd.edu\n" "$username"
    printf "#$ -m abe\n"
    printf "#$ -q %s\n" "${queue:-long}"
    printf "#$ -pe %s\n\n" "${cores:="smp 16"}"
    printf "SIM_NAME=\"%s\"\n" "${inputFile%%.*}"
    printf "WORK_DIR=\`pwd\`\n\n"
    printf "module purge\n"
    printf "module load openmd\n"
    printf "module load CRC_default\n\n"
    printf "fsync \${WORK_DIR}/\${SIM_NAME}.stat &\n"
    printf "fsync \${WORK_DIR}/\${SIM_NAME}.dump &\n"
    printf "fsync \${WORK_DIR}/\${SIM_NAME}.eor &\n"
    printf "fsync \${WORK_DIR}/\${SIM_NAME}.rnemd &\n"
    printf "fsync \$SGE_STDOUT_PATH &\n"
    printf "fsync \$SGE_STDERR_PATH &\n\n"
    printf "cd \${WORK_DIR}\n\n"
    printf "mpirun -np %s openmd_MPI \${SIM_NAME}.omd\n" "${cores#*\ }"
}


### Initial Variables / Default Values ###
declare inputDir inputFile queue scriptDir scriptFile username verbose

queue=long
username="$USER"
verbose=0


### Runtime Configuration ###
while getopts i:s:u:c:dvh opt
do
    case $opt in
        i) FILE   input    = "$OPTARG" ;;                   ## Returns inputFile and inputDir variables
        s) FILE   script   = "$OPTARG" ;;                   ## Returns scriptFile and scriptDir variables
        u) STRING username = "$OPTARG" ;;
        c) STRING cores    = "$OPTARG" ;;
        d) queue=debug ;;
        v) export verbose=1 ;;
        h) printHelpMessage && printFatalErrorMessage 0 ;;
        *) printFatalErrorMessage 1 "Invalid option flag passed to program." ;;
    esac
done


### Main Code ###
[[ ${USER:?Issue finding your CRC username. Set the \$USER variable and try again.} ]]

if [[ -z "${scriptFile:-""}" ]]
then
    if [[ -d "$inputDir" ]]
    then
        cd "$inputDir" || printFatalErrorMessage 2 "Could not change into required directory."

        if [[ -f ${inputFile:?A inputFile is required} ]]
        then
            ## User didn't specify a submission script so we'll just make them one ##
            printOpenmdSubmissionScript > openmd_multiple.sh

            ## Comment out RNEMD line we aren't running RNEMD ##
            if grep useRNEMD "$inputFile" &>/dev/null
            then
                IFS=$' =;'
                useRNEMDArray=( $( grep useRNEMD "$inputFile" ) )
                IFS=$' \t\n'

                if [[ ${useRNEMDArray[1]} == 'false' ]]
                then
                    rnemdLine="fsync \${WORK_DIR}\/\${SIM_NAME}.rnemd \&"
                    sed "s/$rnemdLine/#$rnemdLine/g" openmd_multiple.sh > tempFile && mv tempFile openmd_multiple.sh
                fi
            else
                rnemdLine="fsync \${WORK_DIR}\/\${SIM_NAME}.rnemd \&"
                sed "s/$rnemdLine/#$rnemdLine/g" openmd_multiple.sh > tempFile && mv tempFile openmd_multiple.sh
            fi

            scriptFile=openmd_multiple.sh
        else
            printFatalErrorMessage 3 "The input file provided does not exist."
        fi
    else
        printFatalErrorMessage 4 "Invalid directory."
    fi
elif [[ -d "$scriptDir" ]]
then
    cd "$scriptDir" || printFatalErrorMessage 5 "Could not change into required directory."
else
    printFatalErrorMessage 6 "Invalid directory."
fi

## Submit the jobs if the submission script exists ##
if [[ -f ${scriptFile:?A script is required} ]]
then
    ## If checkQuota script is already running, no need to submit it again ##
    IFS=$'\n'
    qstatArray=( $( qstat -u "$USER" ) )
    IFS=$' \t\n'

    for line in "${qstatArray[@]}"
    do
        lineArray=( $line )

        if [[ "${lineArray[2]}" == "checkUserQ" ]]
        then
            checkUserQuota=1
        elif [[ "${lineArray[2]}" == "checkGroup" ]]
        then
            checkGroupQuota=1
        fi
    done

    if [[ ${checkUserQuota:-0} -eq 0 && "$PWD" == /afs/crc.nd.edu/user/* ]]
    then
        printCheckQuotaScript User > checkUserQuota.sh
        qsub checkUserQuota.sh
    elif [[ ${checkGroupQuota:-0} -eq 0 && "$PWD" == /afs/crc.nd.edu/group/gezelter/* ]]
    then
        printCheckQuotaScript Group > checkGroupQuota.sh
        qsub checkGroupQuota.sh
    fi

    qsub "$scriptFile"
else
    printFatalErrorMessage 7 "The script provided does not exist."
fi
