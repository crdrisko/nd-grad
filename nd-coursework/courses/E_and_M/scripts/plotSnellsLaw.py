#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (c) 2019-2020 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: plotSnellsLaw.py - Version 1.0.0
# Author: cdrisko
# Date: 02/01/2019-09:21:46
# Description: Snell's law plot of light entering BK7 glass at a given angle of incidence

import numpy as np
import matplotlib.pyplot as plt


### Classes and Functions ###
class VisibleLight:
    def __init__(self, refractiveIndex, plotColor):
        self.refractiveIndex = refractiveIndex
        self.plotColor = plotColor

def calculateReflectionAngle(refractiveIndex, n_incident, angle_incident):
    return np.arcsin( (n_incident * np.sin(angle_incident)) / refractiveIndex )


### Main Code ###
n_incident = 1.0
angle_incident = np.pi / 3

## Visible light colors ##
red     = VisibleLight(1.5131, 'r')         ## Red Wavelength Range:    620-750 nm; n_BK7 = 1.5131 @ 700 nm
orange  = VisibleLight(1.5163, '#ffa500')   ## Orange Wavelength Range: 590-620 nm; n_BK7 = 1.5163 @ 600 nm
yellow  = VisibleLight(1.5171, 'y')         ## Yellow Wavelength Range: 570-590 nm; n_BK7 = 1.5171 @ 580 nm
green   = VisibleLight(1.5199, 'g')         ## Green Wavelength Range:  495-570 nm; n_BK7 = 1.5199 @ 525 nm
blue    = VisibleLight(1.5232, 'b')         ## Blue Wavelength Range:   450-495 nm; n_BK7 = 1.5232 @ 475 nm
violet  = VisibleLight(1.5308, '#800080')   ## Violet Wavelength Range: 380-450 nm; n_BK7 = 1.5308 @ 400 nm

## Plotting ##
x1 = np.linspace(-1, 0, 5)
x2 = np.linspace(0, 1, 5)
x3 = np.linspace(.98, 1, 5)

fig, ax1 = plt.subplots()

left, bottom, width, height = [0.75, 0.265, 0.15, 0.15]
ax2 = fig.add_axes([left, bottom, width, height])

ax1.plot(x1, -np.tan(angle_incident) * x1, 'k')

for light in [red, orange, yellow, green, blue, violet]:
    reflectionAngle = calculateReflectionAngle(light.refractiveIndex, n_incident, angle_incident)

    ax1.plot(x2, ( -np.tan(reflectionAngle) )**-1 * x2, color=light.plotColor)
    ax2.plot(x3, ( -np.tan(reflectionAngle) )**-1 * x3, color=light.plotColor)

## Plot adjustments ##
ax2.set_yticklabels([])
ax2.set_xticklabels([])
ax2.axes.get_yaxis().set_ticks([])
ax2.axes.get_xaxis().set_ticks([])

ax1.spines['left'].set_position('zero')
ax1.spines['bottom'].set_position('zero')

ax1.spines['right'].set_color('none')
ax1.spines['top'].set_color('none')

plt.show()
