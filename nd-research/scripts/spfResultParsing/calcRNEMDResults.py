#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (c) 2019-2023 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: calcRNEMDResults.py - Version 1.0.0
# Author: crdrisko
# Date: 09/25/2023-09:30:25
# Description:

import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

### Functions ###
def func(x, a0):
  return a0 * x

def getPlotsBlueGold(percentage):
    percentage_gold  = (100 - percentage) / 100

    data = np.loadtxt("/Users/crdrisko/Desktop/SPF/SPF-Results/Modified Results/ArAr" + str(percentage) + "-mod.txt", delimiter='\t', comments='#')

    N = np.size(data)
    Jp_actual  = percentage_gold * data[0:N:1, 0]
    dblue_dz   = np.abs(data[0:N:1, 1])
    D_blue     = data[0:N:1, 2] * 10

    return Jp_actual, dblue_dz, D_blue

def getPlotsArKr(percentage):
    percentage_Kr  = (100 - percentage) / 100

    data = np.loadtxt("/Users/crdrisko/Desktop/SPF/SPF-Results/Modified Results/ArKr" + str(percentage) + "-mod.txt", delimiter='\t', comments='#')

    N = np.size(data)
    Jp_actual  = percentage_Kr * data[0:N:1, 0]
    dAr_dz     = np.abs(data[0:N:1, 1])
    D_Ar       = data[0:N:1, 2] * 10

    return Jp_actual, dAr_dz, D_Ar

### Main Code ###
for percentage in [10, 25, 50, 75, 90]:
# for percentage in [50, 75, 90]:
    avg_Jp = []

    avg_grad = []
    avg_grad_ci = []

    avg_diff = []
    avg_diff_ci = []

    avg_Jp, avg_grad, avg_diff = getPlotsBlueGold(percentage)
    # avg_Jp, avg_grad, avg_diff = getPlotsArKr(percentage)

    popt, pcov = curve_fit(func, np.array(avg_Jp), avg_grad)

    stdDev = np.sqrt(np.diag(pcov))

    print("D Ar " + str(percentage) + "%: ", end='')

    D_convert_Ar = 1 / popt * (1.66e-21 / 1e-27) * 10
    stdDev_convert_Ar = stdDev / popt**2 * (1.66e-21 / 1e-27) * 10
    print("(%0.4f +/- %0.4f) x 1e-9 m^2 / s" %(D_convert_Ar, stdDev_convert_Ar))

    print()

    fig, axes = plt.subplots(2, 1, figsize=(8, 8), sharex = True)

    axes[0].plot(avg_Jp, avg_grad, marker='o', linestyle='none', color='tab:blue')
    axes[0].plot(avg_Jp, func(np.array(avg_Jp), *popt), color='tab:blue')

    axes[1].plot(avg_Jp, avg_diff, marker='o', linestyle='none', color='tab:blue')
    axes[1].axhline((popt[0])**-1 * (1.66e-21 / 1e-27) * 10, color='tab:blue')

    axes[1].set_xlabel("$J_p$")
    axes[0].set_ylabel("$\\frac{dc}{dz}$")
    axes[1].set_ylabel("D")

    plt.savefig("/Users/crdrisko/Desktop/SPF/SPF-Results/ArgonRed/ArgonRed" + str(percentage) + "_files/RNEMD/Argon" + str(percentage) + ".png")
    # plt.savefig("/Users/crdrisko/Desktop/SPF/SPF-Results/Krypton/Krypton" + str(percentage) + "_files/RNEMD/Argon" + str(percentage) + ".png")
    plt.show()
