#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: bpl_pd.sh - (Listing 11-2)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/14/2019-13:49:06
# Description: Return to previous directory with popd

bpl_pd()
{
    popd
} >/dev/null    ### for the same reason as bpl_cd
