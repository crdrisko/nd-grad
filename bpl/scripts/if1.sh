#!/bin/bash
# Title: if1 - (Listing 3-1)
# Author: Cody R. Drisko (crdrisko)
# Date: 5/12/2019
# Description: Read and check output

read name
if [ -z "$name" ]
then
  echo "No name entered" >&2
  exit 1 			## Set a failed return code
fi
