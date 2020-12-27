#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing13_08.sh
# Author: crdrisko
# Date: 07/29/2019-07:25:12
# Description: Split a record by reading variables

split_record()      #@ USAGE: split_record record delimiter var ...
{
  local record=${1:?} IFS=${2:?}            ## record and delimiter must be provided
  : ${3:?}                                  ## at least one variable is required
  shift 2                                   ## remove record and delimiter, leaving variables

  ## Read record into a list of variables using a 'here document'
  read "$@" <<.
$record
.
}
