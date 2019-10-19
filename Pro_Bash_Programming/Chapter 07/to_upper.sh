#!/bin/bash
# Name: to_upper.sh - (Listing 7-4)
# Author: Cody R. Drisko (crdrisko)
# Date: 07/03/2019-10:40:46
# Description: Convert first character of $1 to uppercase

to_upper()
    case $1 in
        a*) _UPR=A ;; b*) _UPR=B ;; c*) _UPR=C ;; d*) _UPR=D ;;
        e*) _UPR=E ;; f*) _UPR=F ;; g*) _UPR=G ;; h*) _UPR=H ;;
        i*) _UPR=I ;; j*) _UPR=J ;; k*) _UPR=K ;; l*) _UPR=L ;;
        m*) _UPR=M ;; n*) _UPR=N ;; o*) _UPR=O ;; p*) _UPR=P ;;
        q*) _UPR=Q ;; r*) _UPR=R ;; s*) _UPR=S ;; t*) _UPR=T ;;
        u*) _UPR=U ;; v*) _UPR=V ;; w*) _UPR=W ;; x*) _UPR=X ;;
        y*) _UPR=Y ;; z*) _UPR=Z ;;  *) _UPR=${1%${1#?}} ;;
    esac
