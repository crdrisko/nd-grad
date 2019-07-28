#!/bin/bash
# Name: asearch.sh - (Listing 13-3)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/27/2019-10:09:31
# Description: Search elements of an array for a string

asearch()       #@ Search for substring in array; results in array _asearch_elements
{               #@ USAGE: asearch arrayname string
  local arrayname=$1 substring=$2 array
  eval "array=( \"\${$arrayname[@]}\" )"

  case ${array[*]} in
    *"$substring"*) ;;              ## it's there, drop through
    *) return 1 ;;                  ## not there; return error
  esac

  unset _asearch_elements
  for subscript in "${!array[@]}"
  do
    case ${array[$subscript]} in
      *"$substring"*)
        _asearch_elements+=( "${array[$subscript]}" )
        ;;
    esac
  done
}

