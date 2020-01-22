#!/bin/bash
# Name: groupSubmit.sh - Version 1.0.0
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
  printf "  -m  OPTIONAL: Send message to cdrisko@nd.edu with any errors that arrise in\n"
  printf "        the execution of the script. Again, arguments should be wrapped in\n"
  printf "        quotes. Please be detailed in your description of the error.\n\n"
  printf "EXAMPLE: groupSubmit -i testFile -c \"mpi-24 24\" -r\n\n"
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

## Send OSHA-compliant signal words to notify user of potential memory overflow ##
printf -v checkQuotaScript "#!/bin/bash\n\
#$ -N checkQuota\n\
#$ -M %s@nd.edu\n\
#$ -m abe\n\
#$ -pe smp 1\n\n\
while true\n\
do\n\
  quotaArray=( \$( quota | grep u.%s ) )\n\n\
  if [ echo \"\${quotaArray[1]} - \${quotaArray[3]}\" | bc -le 5 ]\n\
  then\n\
    ## Send DANGER if within 5 GB of available quota\n\
    mail -s 'DANGER' %s@nd.edu <<< 'You have <5 GB remaining in quota.'\n\
    sleepTime=5m\n\n\
  elif [ echo \"\${quotaArray[1]} - \${quotaArray[3]}\" | bc -le 50 ]\n\
  then\n\
    ## Send WARNING if within 50 GB of available quota\n\
    mail -s 'WARNING' %s@nd.edu <<< 'You have <50 GB remaining in quota.'\n\
    sleepTime=30m\n\n\
  elif [ echo \"\${quotaArray[1]} - \${quotaArray[3]}\" | bc -le 100 ]\n\
  then\n\
    ## Send CAUTION if within 100 GB of available quota\n\
    mail -s 'CAUTION' %s@nd.edu <<< 'You have <100 GB remaining in quota.'\n\
    sleepTime=1h\n\
  fi\n\n\
  ## Put machine to sleep before next check\n\
  sleep \${sleepTime:-3h}\n\n\
  qstatArray=( \$( qstat -u %s | tail -n +3 ) )\n\
  if [ \${qstatArray[2]} != \"checkQuota\" ]\n\
  then\n\
    exit 0\n\
  fi\n\
done\n" $USER $USER $USER $USER $USER

## The submission script to run the OpenMD job, can be changed as desired ##
printf -v openmdSubmissionScript "#!/bin/bash\n\
#$ -N %s\n\
#$ -M %s@nd.edu\n\
#$ -m abe\n\
#$ -q %s\n\
#$ -pe %s\n\n\
SIM_NAME=\"%s\"\n\
WORK_DIR=\`pwd\`\n\n\
module purge\n\
module load openmd\n\
module load CRC_default\n\n\
fsync \${WORK_DIR}/\${SIM_NAME}.stat &\n\
fsync \${WORK_DIR}/\${SIM_NAME}.dump &\n\
fsync \${WORK_DIR}/\${SIM_NAME}.eor &\n\
fsync \${WORK_DIR}/\${SIM_NAME}.rnemd &\n\
fsync \$SGE_STDOUT_PATH &\n\
fsync \$SGE_STDERR_PATH &\n\n\
cd \${WORK_DIR}\n\n\
mpirun -np %s openmd_MPI \${SIM_NAME}.omd\n" ${fileName:?A filename is required} $USER ${queue:-long}\
 "${cores:="smp 16"}" $fileName "${cores#*\ }"

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

## Quota check is only relevant to jobs submitted in user-space ##
workingDirectory=$( pwd -P )

if [ "${workingDirectory:0:30}" != "/afs/crc.nd.edu/group/gezelter" ] && [ ${checkQuota:-0} -eq 0 ]
then
  printf "$checkQuotaScript" > checkQuota.sh
  qsub checkQuota.sh
fi

printf "$openmdSubmissionScript" > openmd_multiple.sh

## Comment out RNEMD line if specified ##
if [ $useRNEMD -eq 0 ]
then
  rnemdLine="fsync \${WORK_DIR}\/\${SIM_NAME}.rnemd \&"
  sed "s/$rnemdLine/#$rnemdLine/g" openmd_multiple.sh > tempFile && mv tempFile openmd_multiple.sh
fi

qsub openmd_multiple.sh
