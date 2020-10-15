#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (c) 2019-2020 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: mwtccConferencePlots-2019.py - Version 1.0.0
# Author: cdrisko
# Date: 03/21/2020-08:16:56
# Description: Code used for generating the plots shown during my 2019 Midwest Theory Presentation

import numpy as np
import matplotlib.pyplot as plt


### Functions ###
def boundFinder(z, rnemdBound):
    for i in range (0,99):
        roundedValue = np.round(rnemdBound,0)
        if (np.round(z[i],0) == roundedValue):
            return i
        elif (np.round(z[i],0) != roundedValue) and (int(z[i]) == roundedValue):
            return i
        else:
            continue

def rnemd_plotter(fileName):
    rnemd_data = np.loadtxt(fileName, dtype=float, comments='#')
    N = np.size(rnemd_data)
    z = rnemd_data[0:N:1, 0]
    temp = rnemd_data[0:N:1, 1]
    conc_anion = rnemd_data[0:N:1, 6]                           ## the activity (c_i/c_0)
    conc_cation = rnemd_data[0:N:1, 7]                          ## the activity (c_i/c_0)
    E_z = rnemd_data[0:N:1, 10] / 23.06035                      ## V Ang^-1

    return z, temp, conc_anion, conc_cation, E_z


### Parse Input Files ###
z1, temp1, conc_anion1, conc_cation1, E_z1 = rnemd_plotter("01mCa.rnemd")
z2, temp2, conc_anion2, conc_cation2, E_z2 = rnemd_plotter("1mCa.rnemd")
z3, temp3, conc_anion3, conc_cation3, E_z3 = rnemd_plotter("01mLi.rnemd")
z4, temp4, conc_anion4, conc_cation4, E_z4 = rnemd_plotter("1mLi.rnemd")
z5, temp5, conc_anion5, conc_cation5, E_z5 = rnemd_plotter("01mNa.rnemd")
z6, temp6, conc_anion6, conc_cation6, E_z6 = rnemd_plotter("1mNa.rnemd")
z7, temp7, conc_anion7, conc_cation7, E_z7 = rnemd_plotter("1sCa.rnemd")
z8, temp8, conc_anion8, conc_cation8, E_z8 = rnemd_plotter("01sCa.rnemd")
z9, temp9, conc_anion9, conc_cation9, E_z9 = rnemd_plotter("1sLi.rnemd")
z10, temp10, conc_anion10, conc_cation10, E_z10 = rnemd_plotter("01sLi.rnemd")
z11, temp11, conc_anion11, conc_cation11, E_z11 = rnemd_plotter("1sNa.rnemd")
z12, temp12, conc_anion12, conc_cation12, E_z12 = rnemd_plotter("01sNa.rnemd")


### Find the RNEMD Region ###
file = open("1mNa.rnemd", 'r')

line2 = []
line3 = []
while True:
    line = file.readline()
    if not line: break
    if "selectionA" in line:
        line2 = line.split()
    if "selectionB" in line:
        line3 = line.split()
file.close()

file2 = open("1sNa.rnemd", 'r')

line5 = []
line6 = []
while True:
    line1 = file2.readline()
    if not line1: break
    if "selectionA" in line1:
        line5 = line1.split()
    if "selectionB" in line1:
        line6 = line1.split()
file2.close()


### Plotting ###
plt.figure(1)
plt.title("1 M Solutions of Various Ionic Compounds in the Medium Box")
plt.plot(z4, E_z4, "red", label="1M LiCl")
plt.plot(z6, E_z6, "blue", label="1M NaCl")
plt.plot(z2, E_z2, "green", label="1M CaCl$_2$")
plt.axvline(x=z6[boundFinder(z6, float(line3[6]))], color="black", linestyle='-.')
plt.axvline(x=z6[boundFinder(z6, float(line3[10].strip('";')))], color="black",         \
                 linestyle='-.')

plt.xlabel("$z$ $(\\AA)$")
plt.ylabel("$E_z$ $(V/\\AA)$")
plt.legend()


plt.figure(2)
plt.title("Sodium Chloride Concentrations in the Medium Box")
plt.plot(z6, conc_anion6, "green", label="[$Cl^-$]")
plt.plot(z6, conc_cation6, "#FF8C00", label="[$Na^+$]")
plt.axvline(x=z6[boundFinder(z6, float(line3[6]))], color="black", linestyle='-.')
plt.axvline(x=z6[boundFinder(z6, float(line3[10].strip('";')))], color="black",         \
                 linestyle='-.')

plt.xlabel("$z$ $(\\AA)$")
plt.ylabel("Concentration $(M)$")
plt.legend()


plt.figure(3)
plt.title("1 M Solutions of Various Ionic Compounds in the Small Box")
plt.plot(z9, E_z9, "red", label="1M LiCl")
plt.plot(z11, E_z11, "blue", label="1M NaCl")
plt.plot(z7, E_z7, "green", label="1M CaCl$_2$")
plt.axvline(x=z11[boundFinder(z11, float(line6[6]))], color="black", linestyle='-.')
plt.axvline(x=z11[boundFinder(z11, float(line6[10].strip('";')))], color="black",       \
                  linestyle='-.')

plt.xlabel("$z$ $(\\AA)$")
plt.ylabel("$E_z$ $(V/\\AA)$")
plt.legend()


plt.figure(4)
plt.title("Sodium Chloride Concentrations in the Small Box")
plt.plot(z11, conc_anion11, "green", label="[$Cl^-$]")
plt.plot(z11, conc_cation11, "#FF8C00", label="[$Na^+$]")
plt.axvline(x=z11[boundFinder(z11, float(line6[6]))], color="black", linestyle='-.')
plt.axvline(x=z11[boundFinder(z11, float(line6[10].strip('";')))], color="black",       \
                  linestyle='-.')

plt.xlabel("$z$ $(\\AA)$")
plt.ylabel("Concentration $(M)$")
plt.legend(loc=1)
