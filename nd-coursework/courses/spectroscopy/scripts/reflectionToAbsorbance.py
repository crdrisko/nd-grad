#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: reflectionToAbsorbance.py - Version 1.0.0
# Author: cdrisko
# Date: 02/10/2019-11:08:39
# Description: Reproduce absorbance plot from 'Atomically thin MoS2: A new direct-gap semiconductor' paper

import numpy as np
import matplotlib.pyplot as plt
from utilityFunctions import getXYData


### Main Code ###
n_silica = 1.4607                       ## Refractive index of fused silica @ 532 nm
normalizationConstant = 10
pathToFiles = "../samples/semi-conductors/MoS2/dataFiles/"

## Plotting ##
fig, ax1 = plt.subplots()
ax2 = ax1.twinx()

for layer in ["singleLayer", "doubleLayer"]:
    photonEnergy, changeInReflectance = getXYData(pathToFiles + layer + "ReflectionData.csv")
    photonEnergy2, normalizedPL = getXYData(pathToFiles + layer + "PhotoluminescenceData.csv")

    absorbance = ( (n_silica**2 - 1) / 4 ) * (changeInReflectance / 100)

    ## Shift double layer plots up to separate the two layers ##
    if (layer == "doubleLayer"):
        absorbance = (absorbance / 2) + .1
        normalizationConstant = 9.25

    normalizedPL /= normalizationConstant

    ax1.plot(photonEnergy, absorbance, 'k')
    ax1.plot(photonEnergy2, normalizedPL, 'r')

## Plot adjustments ##
ax1.set_xlabel('Photon Energy (eV)')
ax1.set_ylabel('Absorbance/Layer')
ax2.set_ylabel('Normalized PL (a.u.)')

ax1.set_xlim(1.3, 2.4)
ax1.set_ylim(-.025, .3)
ax2.set_ylim(-.025, .3)

## Reproduce annotations on original plots ##
ax1.annotate('A', xy=(1.85, .225), xycoords= 'data')
ax1.annotate('B', xy=(2.0, .22), xycoords= 'data')
ax1.annotate('1', color='b', xy=(1.45, .225), xycoords='data')
ax1.annotate('2lay', xy=(2.25, .175), xycoords='data')
ax1.annotate('1lay', xy=(2.25, .055), xycoords='data')
ax1.annotate('Laser Excitation', color='g', xy=(2.0, .255), xycoords= 'data')
ax1.annotate('(a)', xy=(1.325, .275), xycoords= 'data')

plt.show()
