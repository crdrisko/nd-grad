#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (c) 2019 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for license information.
#
# Name: utilityFunctions.py - Version 1.0.0
# Author: cdrisko
# Date: 04/26/2019-11:46:42
# Description: A collection of utility functions that can be used in other scripts

import numpy as np

def getXYData(fileName, delimiter = ','):
    """
    Import xy data from a given file into two separate numpy arrays. Splits the data on the value of
        delimeter which defaults to ','.
    """
    data = np.loadtxt(fileName, delimiter=delimiter)

    N = np.size(data)
    x_values = data[0:N:1, 0]
    y_values = data[0:N:1, 1]

    return x_values, y_values
