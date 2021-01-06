#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: findConcentration.py - Version 1.0.0
# Author: cdrisko
# Date: 03/21/2020-08:28:56
# Description: Determine the number of particles needed for boxes of specified sizes

import numpy as np
import matplotlib.pyplot as plt


### Functions ###
def findNumberOfMolecules(concentration, x_length, y_length, z_length):
    volume = (x_length * y_length * z_length) * 1E-24 * (1/1000)
    molecules = (concentration * volume) * 6.022E23

    return molecules

def findBoxSize(concentration, numberOfMolecules, xyRatio, xzRatio):
    volume = (numberOfMolecules / concentration) * (1000 / (1E-24 * 6.022E23))
    x_length = np.cbrt( volume / (xyRatio * xzRatio) )
    y_length = x_length * xyRatio
    z_length = x_length * xzRatio

    return x_length, y_length, z_length
