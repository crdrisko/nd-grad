#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Fri Apr 26 11:46:42 2019

Author: crdrisko

Description:
"""

import numpy as np
import matplotlib.pyplot as plt

def data_import(fileName, delimiter):
    """
    Data importing function. fileName should be enclosed in double quotes ("")
        and delimiter should be enclosed in single quotes ('').
        Specified delimiters are ',' and ' '.
    """
    if (delimiter == ','):
        Data = np.loadtxt(fileName, delimiter=",")
        N = np.size(Data)
        x_values = Data[0:N:1, 0]
        y_values = Data[0:N:1, 1]
        return x_values,y_values
    
    elif (delimiter == ' '):
        Data = np.loadtxt(fileName, delimiter=" ")
        N = np.size(Data)
        x_values = Data[0:N:1, 0]
        y_values = Data[0:N:1, 1]
        return x_values,y_values

