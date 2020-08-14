#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: split_passwd.sh - (Listing 13-7)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/29/2019-07:10:09
# Description: Split a passwd record into fields and assign fields to variables

## Split a record from /etc/passwd into fields and assign to variables - (Listing 13-7a)
split_passwd1()     #@ USAGE: split_passwd1 RECORD
{
  local opts=$-                             ## store current shell options
  local IFS=:
  local record=${1:?} array

  set -f                                    ## Turn off filename expansion
  array=( $record )                         ## Split record into array
  case $opts in *f*) ;; *) set +f ;; esac   ## Turn on expansion if previously set

  user=${array[0]}
  passwd=${array[1]}
  uid=${array[2]}
  gid=${array[3]}
  name=${array[4]}
  homedir=${array[5]}
  shell=${array[6]}
}


## Split a record from /etc/passwd into fields and assign to variables - (Listing 13-7b)
split_passwd2()
{
  IFS=: read user passwd uid gid name homedir shell <<.
$1
.
}
