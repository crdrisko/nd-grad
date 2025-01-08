#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (c) 2019-2025 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: calcEMDResults.py - Version 1.0.0
# Author: crdrisko
# Date: 09/25/2023-09:30:25
# Description:

import numpy as np
import matplotlib.pyplot as plt

from sys import argv
import statsmodels.api as sm

def readRCorrFile(cmdLineArg):
    data = np.loadtxt("/Users/crdrisko/Desktop/SPF/SPF-Results/" + cmdLineArg[:-2] + "/" + cmdLineArg + "_files/EMD/RCorr.txt", delimiter='\t', comments='#')

    N = np.size(data)
    time             = data[0:N:1, 0]
    avg_rmsd_blue    = data[0:N:1, 1]
    avg_rmsd_red     = data[0:N:1, 2]
    stdDev_rmsd_blue = data[0:N:1, 3]
    stdDev_rmsd_red  = data[0:N:1, 4]

    wls_model_blue = sm.WLS(avg_rmsd_blue, time, weights = 1 / stdDev_rmsd_blue**2)
    wls_results_blue = wls_model_blue.fit()

    wls_model_red = sm.WLS(avg_rmsd_red, time, weights = 1 / stdDev_rmsd_red**2)
    wls_results_red = wls_model_red.fit()

    # print(wls_results_blue.summary())
    # print(wls_results_red.summary())

    print("Blue: " + str(wls_results_blue.params[0]) + " +/- " + str(wls_results_blue.bse[0]))
    print("Red: " + str(wls_results_red.params[0]) + " +/- " + str(wls_results_red.bse[0]))

def readOnsagerFile(cmdLineArg):
    data = np.loadtxt("/Users/crdrisko/Desktop/SPF/SPF-Results/" + cmdLineArg[:-2] + "/" + cmdLineArg + "_files/EMD/Onsager.txt", delimiter='\t', comments='#')

    N = np.size(data)
    time       = data[0:N:1, 0]
    avg_L11    = data[0:N:1, 1]
    avg_L12    = data[0:N:1, 2]
    avg_L22    = data[0:N:1, 3]
    stdDev_L11 = data[0:N:1, 4]
    stdDev_L12 = data[0:N:1, 5]
    stdDev_L22 = data[0:N:1, 6]

    wls_model_L11 = sm.WLS(avg_L11, time, weights = 1/stdDev_L11**2)
    wls_results_L11 = wls_model_L11.fit()

    wls_model_L12 = sm.WLS(avg_L12, time, weights = 1/stdDev_L12**2)
    wls_results_L12 = wls_model_L12.fit()

    wls_model_L22 = sm.WLS(avg_L22, time, weights = 1/stdDev_L22**2)
    wls_results_L22 = wls_model_L22.fit()

    # print(wls_results_L11.summary())
    # print(wls_results_L12.summary())
    # print(wls_results_L22.summary())

    print("L11: " + str(wls_results_L11.params[0]) + " +/- " + str(wls_results_L11.bse[0]))
    print("L12: " + str(wls_results_L12.params[0]) + " +/- " + str(wls_results_L12.bse[0]))
    print("L22: " + str(wls_results_L22.params[0]) + " +/- " + str(wls_results_L22.bse[0]))

### Main Code ###
readRCorrFile(argv[1])
print()
readOnsagerFile(argv[1])
