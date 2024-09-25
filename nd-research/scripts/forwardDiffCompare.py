#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Name: forwardDiffCompare.py - Version 1.0.0
# Author: crdrisko
# Date: 09/08/2024-07:20:36
# Description:

import numpy as np
import matplotlib.pyplot as plt

from sys import argv

def readStatFile(cmdLineArg):
    data = np.loadtxt(cmdLineArg, comments='#')

    N = np.size(data)
    time              = data[0:N:1, 0]
    totalEnergy       = data[0:N:1, 1]
    potentialEnergy   = data[0:N:1, 2]
    kineticEnergy     = data[0:N:1, 3]
    temperature       = data[0:N:1, 4]
    pressure          = data[0:N:1, 5]
    volume            = data[0:N:1, 6]
    conservedQuantity = data[0:N:1, 7]

    potentialEnergyGrad = -np.diff(potentialEnergy, 1)
    KineticEnergyGrad = np.diff(kineticEnergy, 1)

    with plt.rc_context(fname='nd-grad/nd-research/scripts/spfResultParsing/custom.rc'):
        fig, axes = plt.subplots(2, 1, figsize=(16, 8), sharex = True)

    axes[0].plot(time, temperature, label="Temperature")
    # axes[0].plot(time, totalEnergy, label="Total Energy")
    # axes[0].plot(time, conservedQuantity, color='k', label="Conserved Quantity")

    axes[1].plot(time[:-1], potentialEnergyGrad, marker='o', fillstyle = 'full', markerfacecolor = 'w', label="Potential Energy")
    axes[1].plot(time[:-1], KineticEnergyGrad, marker='s', fillstyle = 'full', markerfacecolor = 'w', label="Kinetic Energy")

    axes[0].legend()
    axes[1].legend()
    plt.show()

### Main Code ###
readStatFile(argv[1])

