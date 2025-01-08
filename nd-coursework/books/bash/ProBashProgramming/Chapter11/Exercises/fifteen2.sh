#!/bin/bash
# Copyright (c) 2019-2025 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: Exercise11_03.sh
# Author: crdrisko
# Date: 07/19/2019-08:51:48
# Description: Place tiles in ascending order

#####################################
## Meta Data
#####################################

scriptname=${0##*/}
description="The Fifteen Puzzle"
author="Chris F.A. Johnson"
created=2009-06-20


#####################################
## Variables
#####################################

board=( {1..15} "" )                            ## The basic board array
target=( "${board[@]}" )                        ## A copy for comparison (the target)
empty=15                                        ## The empty square
last=0                                          ## The last move made
A=0 B=1 C=2 D=3                                 ## Indices into array of possible moves
topleft='\e[0;0H'                               ## Move cursor to top left corner of window
nocursor='\e[?25l'                              ## Make the cursor invisible
normal='\e[0m\e[?12l\e[?25h'                    ## Resume normal operation

## Board layout is a printf format string
## At its most basic, it could be a simple:

fmt1="$nocursor$topleft


    %2s  %2s  %2s  %2s

    %2s  %2s  %2s  %2s

    %2s  %2s  %2s  %2s

    %2s  %2s  %2s  %2s

"

## I prefer this ASCII board
fmt2="\e[?25l\e[0;0H\n
\t+----+----+----+----+
\t|    |    |    |    |
\t| %2s | %2s | %2s | %2s |
\t|    |    |    |    |
\t+----+----+----+----+
\t|    |    |    |    |
\t| %2s | %2s | %2s | %2s |
\t|    |    |    |    |
\t+----+----+----+----+
\t|    |    |    |    |
\t| %2s | %2s | %2s | %2s |
\t|    |    |    |    |
\t+----+----+----+----+
\t|    |    |    |    |
\t| %2s | %2s | %2s | %2s |
\t|    |    |    |    |
\t+----+----+----+----+\n\n"

fmt3="\e[?25l\e[0;0H\n
\t *--*--*--*--*--*--*--*
\t/    \/    \/    \/    \\
\t| %2s || %2s || %2s || %2s |
\t\    /\    /\    /\    /     
\t *--*--*--*--*--*--*--*
\t/    \/    \/    \/    \\
\t| %2s || %2s || %2s || %2s |
\t\    /\    /\    /\    /  
\t *--*--*--*--*--*--*--*
\t/    \/    \/    \/    \\
\t| %2s || %2s || %2s || %2s |
\t\    /\    /\    /\    /  
\t *--*--*--*--*--*--*--*
\t/    \/    \/    \/    \\
\t| %2s || %2s || %2s || %2s |
\t\    /\    /\    /\    /  
\t *--*--*--*--*--*--*--*\n\n"


#####################################
## Functions
#####################################

print_board()   #@ What the name says
{
    case $1 in
        1) printf "$fmt1" "${board[@]}" ;;
        2) printf "$fmt2" "${board[@]}" ;;
        3) printf "$fmt3" "${board[@]}" ;;
        *) printf "Not one of the options...\n"; exit ;;
    esac
}

borders()       #@ List squares bordering on the empty square
{
    ## Calculate x/y co-ordinates of the empty square
    local x=$(( ${empty:=0} % 4 ))  y=$(( $empty / 4 ))

    ## The array, bordering, has 4 elements, corresponding to the 4 directories
    ## If a move in any direction would be off the board, that element is empty
    ##
    unset bordering         ## clear array before setting it
    [ $y -lt 3 ] && bordering[$A]=$(( $empty + 4 ))
    [ $y -gt 0 ] && bordering[$B]=$(( $empty - 4 ))
    [ $x -gt 0 ] && bordering[$C]=$(( $empty - 1 ))
    [ $x -lt 3 ] && bordering[$D]=$(( $empty + 1 ))
}

check()         #@ Check whether puzzle has been solved
{
    ## Compare current board with target
    if [ "${board[*]}" = "${target[*]}" ]
    then
        ## Puzzle is completed, print message and exit
        print_board $which_board
        printf "\a\tCompleted in %d moves\n\n" "$moves"
        exit
    fi
}

move()          #@ Move the square in $1
{
    movelist="$empty $movelist"                 ## add current empty square to the move list
    moves=$(( $moves + 1 ))                     ## increment move counter
    board[$empty]=${board[$1]}                  ## put $1 into the current empty square
    board[$1]=""                                ## remove number from new empty square
    last=$empty                                 ## ... and put it in old empty square
    empty=$1                                    ## set new value for empty-square pointer
}

random_move()   #@ Move one of the squares in the arguments
{
    ## The arguments to random_move are the squares that can be moved
    ## (as generated by the borders function)
    local sq
    while :
    do
        sq=$(( $RANDOM % $# + 1 ))
        sq=${!sq}
        [ $sq -ne ${last:-666} ] &&             ## do not undo last move
            break
    done
    move "$sq"
}

shuffle()       #@ Mix up the board using legitimate moves (to ensure solvable puzzle)
{
    local n=0 max=$(( $RANDOM % 100 +150 ))     ## number of moves to make
    while [ $(( n += 1 )) -lt $max ]
    do
        borders                                 ## generate list of possible moves
        random_move "${bordering[@]}"           ## move to one of them at random
    done
}


#####################################
## End of Functions
#####################################

trap 'printf "$normal"' EXIT                    ## Return terminal to normal state on exit


#####################################
## Instructions and Initialization
#####################################

clear
read -p "Please select a board style: (1, 2, or 3) " which_board
print_board $which_board
echo
printf "\t%s\n" "$description" "by $author, ${created%%-*}" ""
printf "
 Use the cursor keys to move the tiles around.
 
 The game is finished when you return to the
 position shown above.
 
 Try to complete the puzzle in as few moves
 as possible.
 
        Press \e[1mEnter\e[0m to continue
"
shuffle                                         ## randomize board
moves=0                                         ## reset move counter
read -s                                         ## wait for user
clear                                           ## clear the screen


#####################################
## Main Loop
#####################################

while :
do
    borders
    print_board $which_board
    printf "\t   %d move" "$moves"
    [ $moves -ne 1 ] && printf "s"
    check

    ## read a single character without waiting for <ENTER>
    read -sn1 -p $'         \e[K' key
    ## The cursor keys generate three characters: ESC, [ and A, B, C, or D;
    ## this loop will run three times for each press of a cursor key
    ## but will not do anything until it recieves a letter
    ## from the cursor key (or entered directly with A etc.), or a 'q' to exit
    case $key in 
        A) [ -n "${bordering[$A]}" ] && move "${bordering[$A]}" ;;
        B) [ -n "${bordering[$B]}" ] && move "${bordering[$B]}" ;;
        C) [ -n "${bordering[$C]}" ] && move "${bordering[$C]}" ;;
        D) [ -n "${bordering[$D]}" ] && move "${bordering[$D]}" ;;
        q) echo; break ;;
    esac
done
