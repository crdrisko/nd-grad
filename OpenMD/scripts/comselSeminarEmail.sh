#!/bin/bash
# Copyright (c) 2020 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for license information.
#
# Name: comselSeminarEmail.sh - Version 1.0.0
# Author: cdrisko
# Date: 02/18/2020-11:19:02
# Description: 


### Initial Variables / Default Values ###
seminarURL=https://docs.google.com/spreadsheets/d/e/2PACX-1vT6C9KZQRV1mxYgHD0Zl7YJD-p_3rrr5ZW94_3K\
rc7GekH6NuDvUls8MGGylVbtQhVXKLy-Sak_bK-2/pub?output=csv

emailSubject="Super Group Seminar Today"
emailHeader="Hello Everyone,"
emailSignature="-- 
Cody Drisko
Graduate Student, Gezelter Lab
Department of Chemistry and Biochemistry
University of Notre Dame | Notre Dame, IN 46556"


### Main Code ###
IFS=$'\n'
seminarScheduleData=( $( wget -q -O- $seminarURL) )
IFS=$','

for line in "${seminarScheduleData[@]:2}"
do 
    lineArray=( $line )

    todaysDate=$(date '+%-m/%-d/%Y')

    date="${lineArray[0]}"
    talkA_name="${lineArray[1]}"
    talkA_email="${lineArray[2]}"
    talkB_name="${lineArray[3]}"
    talkB_email="${lineArray[4]}"

    if [ $todaysDate == $date ]
    then
        ## Two talks today beginning at 12:00PM ##
        if ! [ -z $talkA_name ] && ! [ -z $talkB_name ]
        then
            timeOfTalk=noon
            printf -v message\
                "%s\n\nJust a quick reminder: we will be hearing from %s and %s today at %s.\n\n%s\n"\
                "$emailHeader" "$talkA_name" "$talkB_name" "$timeOfTalk" "$emailSignature"

            printf "%s\n" "$message" | mail -s "$emailSubject" cdrisko@nd.edu
        
        ## One talk today beginning at 12:00PM ##
        elif ! [ -z $talkA_name ] && [ -z $talkB_name ] && [[ "${talkA_name}" != *" Break" ]]
        then
            timeOfTalk=12:00PM
            printf -v message\
                "%s\n\nJust a quick reminder: we will be hearing from %s today at %s.\n\n%s\n"\
                "$emailHeader" "$talkA_name" "$timeOfTalk" "$emailSignature"
                
            printf "%s\n" "$message" | mail -s "$emailSubject" cdrisko@nd.edu
            
        ## One talk today beginning at 12:30PM ##
        elif [ -z $talkA_name ] && ! [ -z $talkB_name ]
        then
            timeOfTalk=12:30PM
            printf -v message\
                "%s\n\nJust a quick reminder: we will be hearing from %s today at %s.\n\n%s\n"\
                "$emailHeader" "$talkB_name" "$timeOfTalk" "$emailSignature"
                
            printf "%s\n" "$message" | mail -s "$emailSubject" cdrisko@nd.edu

        ## No scheduled talks today ##
        elif [ -z $talkA_name ] && [ -z $talkB_name ]
        then
            printf -v message\
                "%s\n\nThere will be no meeting today.\n\n%s\n"\
                "$emailHeader" "$emailSignature"

            printf "%s\n" "$message" | mail -s 'No meeting today' cdrisko@nd.edu
        fi
    fi
done

