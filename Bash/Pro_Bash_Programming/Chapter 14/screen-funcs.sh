#!/bin/bash
# Name: screen-funcs.sh - (Listing 14-1)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/29/2019-13:26:55
# Description: Library of screen manuipulation functions


## Sourcing the screen-vars libray - (Listing 14-1a)
. screen-vars.sh


## Place the cursor at a specified location and print optional string - (Listing 14-1b)
printat()         #@ USAGE: printat [row [column [string]]]
{
  printf "${cu_row_col?}" ${1:-1} ${2:-1}
  if [ $# -gt 2 ]
  then 
    shift 2
    printf "%s" "$*"
  fi
}


## Print a block of text anywhere on the screen - (Listing 14-1c)
put_block()       #@ Print arguments in a block beginning at the current position
{
  printf "$cu_save"                     ## save cursor location
  printf "%s$cu_NL" "$@"                ## restore cursor location, move line down, save cursor
}

put_block_at()    #@ Print arguments in a block at the position in $1 and $2
{
  printat "$1" "$2"
  shift 2
  put_block "$@"
}


## Store length of longest argument in _MAX_LENGTH - (Listing 14-1d)
_max_length()     #@ Store length of longest argument in _MAX_LENGTH
{
  local var
  _MAX_LENGTH=${#1}                     ## initialize with length of first parameter
  shift                                 ## ... and remove first parameter
  for var                               ## loop through remaining parameters
  do 
    [ "${#var}" -gt "$_MAX_LENGTH" ] && _MAX_LENGTH=${#var}
  done
}


## Clear area and print block - (Listing 14-1e)
print_block()     #@ Print arguments in block with space around them
{
  local _MAX_LENGTH
  _max_length "$@"
  printf "$cu_save"
  printf " %-${_MAX_LENGTH}s $cu_NL" " " "$@" " "
}

print_block_at()  #@ Move to position. remove 2 parameters and call print_block
{
  printat $1 $2
  shift 2
  print_block "$@"
}


## Split string into array with elements not exceeding maximum length - (Listing 14-1f)
wrap()            #@ USAGE: wrap string length
{                 #@ requires bash-3.1 or later
  local words=$1 textwidth=$2 line= opts=$-
  local len=0 templen=0
  set -f

  unset -v wrap
  for word in $words
  do
    templen=$(( $len + 1 + ${#word} ))  ## test adding a word
    if [ "$templen" -gt "$textwidth" ]  ## does adding a word exceed length?
    then
      wrap+=( "$line" )                 ## yes, store line in array
      printf -v line "%s" "$word"       ## begin new line
      len=${#word}
    else 
      len=$templen                      ## no, add word to line
      printf -v line "%s" "${line:+"$line "}" "$word"
    fi
  done
  wrap+=( "$line" )

  case $opts in
    *f*) ;;
    *) set +f ;;
  esac
}
