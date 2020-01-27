#!/bin/bash
# Name: groupSubmit.sh - Version 1.0.2
# Author: cdrisko
# Date: 01/20/2020-10:22:05
# Description: Gezelter group submission script creator


### Functions ###
printHelpMessage()      #@ DESCRIPTION: Print the groupSubmit program's help message
{                       #@ USAGE: printHelpMessage
  printf "\nUSAGE: groupSubmit [-hr] [-i fileName] [-c cores] [-q queue]\n"
  printf "    [-m message]\n\n"
  printf "  -h  Prints help information about the groupSubmit program.\n"
  printf "  -r  Check for RNEMD outputs. Defaults to false/off.\n\n"
  printf "  -i  REQUIRED: The base filename of your .omd file to be submitted.\n"
  printf "  -c  OPTIONAL: The queuing system and number of cores required. Arguments\n"
  printf "        should be wrapped in quotes. Default is smp 16.\n"
  printf "  -q  OPTIONAL: Queuing system you wish to use. Default is long, the other\n"
  printf "        option is debug.\n"
  printf "  -m  OPTIONAL: Send message to cdrisko@nd.edu with any errors that arise in\n"
  printf "        the execution of the script. Again, arguments should be wrapped in\n"
  printf "        quotes. Please be detailed in your description of the error.\n\n"
  printf "EXAMPLE: groupSubmit -i testFile -c \"mpi-24 24\" -r\n\n"
}

printCheckQuotaScript()     #@ DESCRIPTION: Print script used to notify user of potential memory overflow
{                           #@ USAGE: printCheckQuotaScript
  printf "#!/bin/bash\n"
  printf "#$ -N checkQuota\n"
  printf "#$ -M %s@nd.edu\n" $USER
  printf "#$ -m abe\n"
  printf "#$ -pe smp 1\n\n"
  printf "while true\n"
  printf "do\n"
  printf "  quotaArray=( \$( /usr/bin/fs quota ) )\n"
  printf "  quotaPercentage=\${quotaArray[0]}\n"
  printf "  quotaPercentage=\${quotaPercentage%%%%\\%%*}\n\n"
  printf "  if [ \$quotaPercentage -ge 99 ]\n"
  printf "  then\n"
  printf "    ## Send DANGER if within 1%% of available quota\n"
  printf "    mail -s 'DANGER' %s@nd.edu <<< 'You have used 99%% of your available quota.'\n" $USER
  printf "    sleepTime=5m\n\n"
  printf "  elif [ \$quotaPercentage -ge 95 ]\n"
  printf "  then\n"
  printf "    ## Send WARNING if within 5%% of available quota\n"
  printf "    mail -s 'WARNING' %s@nd.edu <<< 'You have used 95%% of your available quota.'\n" $USER
  printf "    sleepTime=30m\n\n"
  printf "  elif [ \$quotaPercentage -ge 90 ]\n"
  printf "  then\n"
  printf "    ## Send CAUTION if within 10%% of available quota\n"
  printf "    mail -s 'CAUTION' %s@nd.edu <<< 'You have used 90%% of your available quota.'\n" $USER
  printf "    sleepTime=1h\n"
  printf "  fi\n\n"
  printf "  ## Put machine to sleep before next check\n"
  printf "  sleep \${sleepTime:=3h}\n\n"
  printf "  qstatArray=( \$( /opt/sge/bin/lx-amd64/qstat -u %s | tail -n +3 ) )\n" $USER
  printf "  qstatArrayLength=\$( printf \"%%s\\\n\" \${qstatArray[@]} | wc -l )\n\n"
  printf "  if [ \${qstatArray[2]} == \"checkQuota\" ] && [ \$qstatArrayLength -eq 9 ]\n"
  printf "  then\n"
  printf "    exit 0\n"
  printf "  fi\n"
  printf "done\n"
}

printOpenmdSubmissionScript()   #@ DESCRIPTION: Print script used to run the OpenMD job
{                               #@ USAGE: printOpenmdSubmissionScript
  printf "#!/bin/bash\n"
  printf "#$ -N %s\n" ${fileName:?A filename is required}
  printf "#$ -M %s@nd.edu\n" $USER
  printf "#$ -m abe\n"
  printf "#$ -q %s\n" ${queue:-long}
  printf "#$ -pe %s\n\n" "${cores:="smp 16"}"
  printf "SIM_NAME=\"%s\"\n" $fileName
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
useRNEMD=0


### Runtime Configuration ###
while getopts i:c:q:m:rh opt
do
  case $opt in
    i) fileName=$OPTARG ;;
    c) cores="$OPTARG" ;;
    q) queue=$OPTARG ;;
    m) echo "$OPTARG" | mail -s 'groupSubmit Script Issues' cdrisko@nd.edu
       exit 1 ;;
    r) useRNEMD=1 ;;
    h) printHelpMessage
       exit 0 ;;
  esac
done

### Main Code ###
[ ${USER:?Issue finding your CRC username. Set the \$USER variable and try again.} ]

## If checkQuota script is already running, no need to submit it again ##
IFS=$'\n'
array=( $( qstat -u $USER ) )
IFS=$' \t\n'

for line in "${array[@]}"
do
  newArray=( $line )

  if [ "${newArray[2]}" = "checkQuota" ]
  then
    checkQuota=1
  fi
done

if [ ${checkQuota:-0} -eq 0 ]
then
  printCheckQuotaScript > checkQuota.sh
  qsub checkQuota.sh
fi

printOpenmdSubmissionScript > openmd_multiple.sh

## Comment out RNEMD line if specified ##
if [ $useRNEMD -eq 0 ]
then
  rnemdLine="fsync \${WORK_DIR}\/\${SIM_NAME}.rnemd \&"
  sed "s/$rnemdLine/#$rnemdLine/g" openmd_multiple.sh > tempFile && mv tempFile openmd_multiple.sh
fi

qsub openmd_multiple.sh
