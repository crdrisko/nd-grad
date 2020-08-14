#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for license information.
#
# Name: stringgrid-funcs.sh - (Listing 13-5)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/28/2019-06:59:19
# Description: Working with single string grids


## Create a grid and fill it - (Listing 13-5a)
initgrid()      #@ Fill N x N grid with a character
{               #@ USAGE: initgrid gridname size [character]
  ## If a parameter is missing, it's a programming error so exit
  local grid gridname=${1:?} char=${3:- } size
  export gridsize=${2:?}                            ## set gridsize globally

  size=$(( $gridsize ** 2 ))                        ## total number of characters in grid
  printf -v grid "%$size.${size}s" " "              ## print string of spaces to variable
  eval "$gridname=\${grid// /"$char"}"              ## replaces spaces with desired character
}


## Calculate index from row and column - (Listing 13-5b)
gridindex()     #@ Store row/column's index into string in var or $_GRIDINDEX
{               #@ USAGE: gridindex row column [gridsize] [var]
  local row=${1:?} col=${2:?}

  ## If gridsize argument is not given, take it from definition in calling script
  local gridsize=${3:-$gridsize}
  printf -v "${4:-_GRIDINDEX}" "%d" "$(( ($row - 1) * $gridsize + $col - 1 ))"
}


## Insert character in grid at specified row and column - (Listing 13-5c)
putgrid()       #@ Insert character in a grid at row and column
{               #@ USAGE: putgrid gridname row column char
  local gridname=$1                 ## grid variable name
  local left right                  ## string to left and right of character to be changed
  local index                       ## result from gridindex function
  local char=${4:?}                 ## character to place in grid
  local grid=${!gridname}           ## get grid string through indirection

  gridindex ${2:?} ${3:?} "$gridsize" index

  left=${grid:0:index}
  right=${grid:index+1}
  grid=$left$4$right
  eval "$gridname=\$grid"
}


## Get character at row and column location in grid - (Listing 13-5d)
getgrid()       #@ Get character from grid in row Y, column X
{               #@ USAGE: getgrid gridname row column var
  : ${1:?} ${2:?} ${3:?} ${4:?}
  local grid=${!1}
  gridindex "$2" "$3"
  eval "$4=\${grid:_GRIDINDEX:1}"
}


## Print a grid from a string - (Listing 13-5e)
showgrid()      #@ print grid in rows to stdout
{               #@ USAGE: showgrid gridname [gridsize]
  local grid=${!1:?} gridsize=${2:-$gridsize}
  local row                         ## the row to be printed, then removed from local copy of grid

  while [ -n "$grid" ]              ## loop until there's nothing left
  do
    row=${grid:0:$gridsize}         ## get first $gridsize characters from grid
    printf "\t:%s:\n" "$row"        ## print the row
    grid=${grid#"$row"}             ## remove $row from front of grid
  done
}


## Print a grid in reverse order - (Listing 13-5f)
rshowgrid()     #@ print grid to stdout in reverse order
{               #@ USAGE: rshowgrid grid [gridsize]
  local grid gridsize=${2:-$gridsize} row
  grid=${!1:?}
  while [ -n "$grid" ]
  do 
    ## Note space before minus sign
    ## to distinguish it from default value substitution
    row=${grid: -$gridsize}         ## get last row from grid
    printf "\t:%s:\n" "$row"        ## print it
    grid=${grid%"$row"}             ## remove it
  done
}
