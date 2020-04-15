#!/bin/bash
# Name: bpl_k.sh - (Listing 11-14)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/18/2019-07:51:03
# Description: List commands whose short descriptions include a search string

bpl_k()     #@ USAGE: k string
{
    man -k "$@" | grep '(1'
}
