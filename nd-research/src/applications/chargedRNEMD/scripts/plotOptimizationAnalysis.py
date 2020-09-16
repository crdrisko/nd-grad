#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (c) 2020 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: plotOptimizationAnalysis.py - Version 1.0.0
# Author: cdrisko
# Date: 03/21/2020-08:00:04
# Description: Plot the results for the method optimization strategy of varying the applied current density

import numpy as np
import matplotlib.pyplot as plt
from sys import argv

fileName = argv[1]

data = np.loadtxt(fileName, dtype=float, comments="#")
N = np.size(data)

Regions     = data[0:N:1, 0]
Jc_Anion    = data[0:N:1, 1]
Jc_Cation   = data[0:N:1, 2]
SlabWidth   = data[0:N:1, 3]
FailedKicks = data[0:N:1, 4]
Jc_target   = np.array( (Jc_Anion + Jc_Cation) / (1 - (FailedKicks / 100)) )

## Plot for the target current density vs. the actual applied current density ##
plt.figure("Target Jc")
plt.plot(Jc_target, Jc_Anion + Jc_Cation, marker='o', linestyle='None')
plt.plot(Jc_target, Jc_target)

plt.xlabel("Target Current Density ($e/\\AA^2/fs$)")
plt.ylabel("Applied Current Density ($e/\\AA^2/fs$)")


numberOfRegions = int(Regions[-1])

for ionicSpecies in range (0, 2):
    ## Generate the figures and axes for each of the plots ##
    fig1, ax1 = plt.subplots(1, numberOfRegions, figsize=(int(7 * (numberOfRegions / 2)), 5),
                    sharex=True, sharey=True, squeeze=True)

    fig2, ax2 = plt.subplots(1, numberOfRegions, figsize=(int(7 * (numberOfRegions / 2)), 5),
                    sharex=True, sharey=True, squeeze=True)

    if (ionicSpecies == 0):
        ionicSpeciesLabel = "Anion"
    else:
        ionicSpeciesLabel = "Cation"

    fig1.canvas.set_window_title("Grad ECP " + ionicSpeciesLabel)
    fig2.canvas.set_window_title("Lambda " + ionicSpeciesLabel)

    for currentRegion in range (0, numberOfRegions):
        Jc_Applied   = data[currentRegion:N:numberOfRegions,     ionicSpecies + 1]
        GradECP      = data[currentRegion:N:numberOfRegions, 2 * ionicSpecies + 5]
        GradECPError = data[currentRegion:N:numberOfRegions, 2 * ionicSpecies + 6]
        Lambda       = data[currentRegion:N:numberOfRegions, 2 * ionicSpecies + 9]
        LambdaError  = data[currentRegion:N:numberOfRegions, 2 * ionicSpecies + 10]
        slabWidth    = SlabWidth[currentRegion:N:numberOfRegions]


        ## Plot for the Gradient of the Electrochemical Potential ##
        ax1[currentRegion].set_title("Region " + str(currentRegion + 1))
        ax1[currentRegion].plot(Jc_Applied, GradECP, marker='o', linestyle='None')
        ax1[currentRegion].errorbar(Jc_Applied, GradECP, yerr=(1.96 * GradECPError), linestyle='None')

        ax1[0].set_xlabel("Applied Current Density ($e/\\AA^2/fs$)")
        ax1[0].set_ylabel("$\\nabla \\mu'$ ($eV/Ang$)")

        fig1.tight_layout()


        ## Plot for the Molar Conductivity ##
        ax2[currentRegion].set_title("Region " + str(currentRegion + 1))
        ax2[currentRegion].plot(Jc_Applied, Lambda, marker='o', linestyle='None')
        ax2[currentRegion].errorbar(Jc_Applied, Lambda, yerr=(1.96 * LambdaError), linestyle='None')

        ax2[0].set_xlabel("Applied Current Density ($e/\\AA^2/fs$)")
        ax2[0].set_ylabel("$\\lambda$ ($Scm^2/mol$)")

        fig2.tight_layout()

plt.show()
