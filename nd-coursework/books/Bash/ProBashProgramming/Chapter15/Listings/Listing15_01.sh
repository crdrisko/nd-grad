#!/bin/bash
# Copyright (c) 2010 Chris Johnson. Some rights reserved.
# Licensed under the Freeware License. See the LICENSE file in the project root for more information.
#
# Name: Listing15_01.sh
# Author: crdrisko
# Date: 08/10/2019-08:30:55
# Description: Read a single keypress

ESC=$'\e'
CSI=$'\e['


## Functions for reading a single keypress - (Listing 15-1a)
_key()
{
  IFS= read -r -s -n1 -d '' "${1:-_KEY}"
}


## Read a sequence of characters from a function or cursor key - (Listing 15-1b)
_keys()     #@ Store all waiting keypresses in $_KEYS
{
  _KEYS=
  __KX=

  ## ESC_END is a list of characters that can end a key sequence
  ## Some terminal emulations may have others; adjust to taste
  ESC_END=[a-zA-NP-Z~^\$@$ESC]

  while :
  do
    IFS= read -rsn1 -d '' -t1 __KX
    _KEYS=$_KEYS$__KX
    case $__KX in
      "" | $ESC_END ) break ;;
    esac
  done
}


## Translate a string to a key name - (Listing 15-1c)
_esc2key()
{
  case $1 in
    ## Cursor keys
    "$CSI"A | ${CSI}OA ) _ESC2KEY=UP ;;
    "$CSI"B | ${CSI}OB ) _ESC2KEY=DOWN ;;
    "$CSI"C | ${CSI}OC ) _ESC2KEY=RIGHT ;;
    "$CSI"D | ${CSI}OD ) _ESC2KEY=LEFT ;;

    ## Function keys (unshifted)
    "$CSI"11~ | "$CSI["A | ${ESC}OP ) _ESC2KEY=F1 ;;
    "$CSI"12~ | "$CSI["B | ${ESC}OQ ) _ESC2KEY=F2 ;;
    "$CSI"13~ | "$CSI["C | ${ESC}OR ) _ESC2KEY=F3 ;;
    "$CSI"14~ | "$CSI["D | ${ESC}OS ) _ESC2KEY=F4 ;;
    "$CSI"15~ | "$CSI["E ) _ESC2KEY=F5 ;;
    "$CSI"17~ | "$CSI["F ) _ESC2KEY=F6 ;;
    "$CSI"18~ ) _ESC2KEY=F7 ;;
    "$CSI"19~ ) _ESC2KEY=F8 ;;
    "$CSI"20~ ) _ESC2KEY=F9 ;;
    "$CSI"21~ ) _ESC2KEY=F10 ;;
    "$CSI"23~ ) _ESC2KEY=F11 ;;
    "$CSI"24~ ) _ESC2KEY=F12 ;;

    ## Insert, Delete, Home, End, Page Up, Page Down
    "$CSI"2~ ) _ESC2KEY=INS ;;
    "$CSI"3~ ) _ESC2KEY=DEL ;;
    "$CSI"[17]~ | "$CSI"H ) _ESC2KEY=HOME ;;
    "$CSI"[28]~ | "$CSI"F ) _ESC2KEY=END ;;
    "$CSI"5~ ) _ESC2KEY=PGUP ;;
    "$CSI"6~ ) _ESC2KEY=PGDN ;;

    ## Everything else; add other keys before this line
    *) _ESC2KEY=UNKNOWN ;;
  esac
  [ -n "$2" ] && eval "$2=\$_ESC2KEY"
}


## Gets a key and, if necessary, translates it to a key name - (Listing 15-1d)
get_key()
{
  _key
  case $_KEY in
    "$ESC") _keys
            _esc2key "$ESC$_KEYS" _KEY
            ;;
  esac
}


## Reads a key and, if more than a single character, translates it to a key name - (Listing 15-1e)
get_key()   #@ USAGE: get_key var
{
  local _v_ _w_ _x_ _y_ _z_ delay=${delay:-.0001}
  IFS= read -d '' -rsn1 _v_
  read -sn1 -t "$delay" _w_
  read -sn1 -t "$delay" _x_
  read -sn1 -t "$delay" _y_
  read -sn1 -t "$delay" _z_
  case $_v_ in
    $'\e') _esc2key "$_v_$_w_$_x_$_y_$_z_"
           printf -v ${1:?} $_ESC2KEY
           ;;
    *) printf -v ${1:?} "%s" "$_v_$_w_$_x_$_y_$_z_" ;;
  esac
}
