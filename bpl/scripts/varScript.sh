#!/bin/bash 
# Name: varScript.sh - (Exercise 5-3)                                          
# Author: Cody R. Drisko (crdrisko)                       
# Date: 05/18/19-22:27:24                                 
# Description: Finds the second number of var using parameter expansion

var=192.168.0.123
printf "The second number in var is %s\n" "${var:4:3}"


