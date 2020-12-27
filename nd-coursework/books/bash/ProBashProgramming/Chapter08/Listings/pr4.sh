#!/bin/bash
# Name: pr4.sh
# Author: crdrisko
# Date: 07/13/2019-11:13:57
# Description: Function to print its arguments in four equal columns

pr4()
{
    ## calculate column width
    local width=$(( (${COLUMNS:-80} - 2) / 4 ))

    ## Note that braces are necessary on the second $width to separate it from 's'
    local s=%-$width.${width}s
    printf "$s $s $s $s\n" "$@"
}
