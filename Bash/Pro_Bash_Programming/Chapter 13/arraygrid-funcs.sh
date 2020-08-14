#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: arraygrid-funcs.sh - (Listing 13-6)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/28/2019-14:03:12
# Description: Two dimensional grids using arrays


## Initialize a grid array - (Listing 13-6a)
initagrid()         #@ Fill N x N grid with supplied data (or placeholders if none)
{                   #@ USAGE: initagrid gridname size [character...]
  ## If a required parameter is missing, it's a programming error, so exit
  local grid gridname=${1:?} char=${3:- } size
  export agridsize=${2:?}                   ## set agridsize globally

  size=$(( $agridsize * $agridsize ))       ## total number of elements in grid

  shift 2                                   ## remove first two arguments, gridname and agridsize
  grid=( "$@" )                             ## what's left goes into the array

  while [ ${#grid[@]} -lt $size ]
  do
    grid+=( "" )
  done

  eval "$gridname=( \"\${grid[@]}\" )"
}


## Calculate index from row and column 
agridindex()        #@ Store row/column's index into string in var or $_AGRIDINDEX
{                   #@ USAGE: agridindex row column [agridsize] [var]
  local row=${1:?} col=${2:?}

  ## If gridsize argument is not given, take it from definition in calling script
  local agridsize=${3:-$agridsize}
  printf -v "${4:-_AGRIDINDEX}" "%d" "$(( ($row - 1) * $agridsize + $col - 1 ))"
}


## Replace a grid element - (Listing 13-6b)
putagrid()          #@ Replace character in grid at row and column
{                   #@ USAGE: putagrid gridname row column char
  local left right pos grid gridname=$1
  local value=${4:?} index
  agridindex ${2:?} ${3:?} "$agridsize" index       ## calculate the index
  eval "$gridname[index]=\$value"                   ## assign the value
}


## Extract an entry from a grid - (Listing 13-6c)
getagrid()          #@ Get entry from grid in row Y, column X
{                   #@ USAGE: getagrid gridname row column var
  : ${1:?} ${2:?} ${3:?} ${4:?}
  local grid
  
  eval "grid=( \"\${$1[@]}\" )"
  agridindex "$2" "$3"
  eval "$4=\${grid[$_AGRIDINDEX]}"
}


## Print the grid from the array - (Listing 13-6d)
showagrid()         #@ Print grid to stdout
{                   #@ USAGE: showagrid gridname format [agridsize]
  local gridname=${1:?} grid
  local format=${2:?}
  local agridsize=${3:-${agridsize:?}} row

  eval "grid=( \"\${$1[@]}\" )"
  printf "$format" "${grid[@]}"
}


## Print a grid in reverse order - (Listing 13-6e)
rshowagrid()        #@ Print grid to stdout in reverse order
{                   #@ USAGE: rshowagrid gridname format [agridsize]
  local format=${2:?} temp grid
  local agridsize=${3:-$agridsize} row
  eval "grid=( \"\${$1[@]}\" )"
  while [ "${#grid[@]}" -gt 0 ]
  do
    ## Note space before minus sign
    ## to distinguish ot from default value substitution
    printf "$format" "${grid[@]: -$agridsize}"
    grid=( "${grid[@]:0:${#grid[@]}-$agridsize}" )
  done
}
