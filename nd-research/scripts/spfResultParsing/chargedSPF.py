#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Name: chargedSPF.py - Version 1.0.0
# Author: crdrisko
# Date: 11/01/2024-05:40:16
# Description:

import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

### Functions ###
def func(x, a0, a1):
  return a0 * (1 - np.exp(-x / a1))

def getDataNaCl(exchangePeriod, seed):
    data = np.loadtxt("/Users/crdrisko/Desktop/Charge/NaCl/spf" + str(exchangePeriod) + "_ps/RNEMD" + str(seed) + ".csv", delimiter=',', comments='#')

    N = np.size(data)
    time       = data[0:N:1, 0] / 100
    Jc_applied = data[0:N:1, 1]
    Jc_actual  = data[0:N:1, 2]
    dNa_dz     = data[0:N:1, 3]
    dCl_dz     = data[0:N:1, 4]
    eField     = data[0:N:1, 5]

    return time, dNa_dz, dCl_dz, eField

def getDataCaCl2(exchangePeriod, seed):
    data = np.loadtxt("/Users/crdrisko/Desktop/Charge/CaCl2/spf" + str(exchangePeriod) + "_ps/RNEMD" + str(seed) + ".csv", delimiter=',', comments='#')

    N = np.size(data)
    time       = data[0:N:1, 0] / 100
    Jc_applied = data[0:N:1, 1]
    Jc_actual  = data[0:N:1, 2]
    dCa_dz     = data[0:N:1, 3]
    dCl_dz     = data[0:N:1, 4]
    eField     = data[0:N:1, 5]

    return time, dCa_dz, dCl_dz, eField


### Main Code ###
temp_Time = [[], [], [], [], []]
avg_Time = []

temp_cationGrad = [[], [], [], [], []]
avg_cationGrad = []
err_cationGrad = []

temp_anionGrad = [[], [], [], [], []]
avg_anionGrad = []
err_anionGrad = []

temp_eField = [[], [], [], [], []]
avg_eField = []
err_eField = []

for exchangePeriod in [14, 16, 22, 30, 40, 60]:
# for exchangePeriod in [14, 16, 22]:
    count = 0
    for seed in [5, 6, 7, 8, 9]:
        temp_Time[count], temp_cationGrad[count], temp_anionGrad[count], temp_eField[count] = getDataCaCl2(exchangePeriod, seed)

        if count == 0:
            avg_Time = temp_Time[count]
            avg_cationGrad = temp_cationGrad[count]
            avg_anionGrad = temp_anionGrad[count]
            avg_eField = temp_eField[count]
        else:
            avg_Time += temp_Time[count]
            avg_cationGrad += temp_cationGrad[count]
            avg_anionGrad += temp_anionGrad[count]
            avg_eField += temp_eField[count]

        count += 1
    
    avg_Time /= count
    avg_cationGrad /= count
    avg_anionGrad /= count
    avg_eField /= count

    count = 0
    for seed in [5, 6, 7, 8, 9]:
        if count == 0:
            err_cationGrad = (temp_cationGrad[count] - avg_cationGrad)**2
            err_anionGrad = (temp_anionGrad[count] - avg_anionGrad)**2
            err_eField = (temp_eField[count] - avg_eField)**2
        else:
            err_cationGrad += (temp_cationGrad[count] - avg_cationGrad)**2
            err_anionGrad += (temp_anionGrad[count] - avg_anionGrad)**2
            err_eField += (temp_eField[count] - avg_eField)**2
        
        count += 1

    err_cationGrad = np.sqrt(err_cationGrad / 4) / np.sqrt(5)
    err_anionGrad = np.sqrt(err_anionGrad / 4) / np.sqrt(5)
    err_eField = np.sqrt(err_eField / 4) / np.sqrt(5)

    print(1 / (exchangePeriod * 1000 * 2 * 25 * 25) / avg_eField[-1] * (1e15 * 1e10 * 1.602e-19) * 10)

    with plt.rc_context(fname='nd-grad/nd-research/scripts/spfResultParsing/custom.rc'):
        plt.errorbar(avg_Time, avg_cationGrad, err_cationGrad, marker='o', markerfacecolor = 'w', linestyle='none')
        plt.errorbar(avg_Time, avg_anionGrad, err_anionGrad, marker='o', markerfacecolor = 'w', linestyle='none')
        plt.errorbar(avg_Time, avg_eField, err_eField, marker='o', markerfacecolor = 'w', linestyle='none')

    plt.savefig("/Users/crdrisko/Desktop/Charge/CaCl2/spf" + str(exchangePeriod) + "_ps-long.png")
    plt.show()

