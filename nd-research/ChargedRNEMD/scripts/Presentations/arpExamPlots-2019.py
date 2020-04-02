#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (c) 2020 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for license information.
#
# Name: arpExamPlots-2019.py - Version 1.0.0
# Author: cdrisko
# Date: 03/21/2020-08:11:31
# Description: Code used for generating the plots shown during my ARP Exam

import numpy as np
import matplotlib.pyplot as plt
from sys import argv
import statsmodels.api as sm


### Functions ###
def getAverages(quantity, points):
    quantity_avg = np.zeros(np.size(quantity) // points)
    count = 0
    for i in range(0, np.size(quantity_avg)):
        for j in range(0, points):
            quantity_avg[i] += quantity[j + count]
        count += points

        quantity_avg[i] /= points
    return quantity_avg

def lennardJones(sigma, epsilon, r):
    return 4 * epsilon * ( (sigma / r)**12 - (sigma / r)**6 )


### Plotting rcorr Results ###
dirName = argv[1]

anData = np.loadtxt(dirName + "an.rcorr", dtype=float, comments='#')
catData = np.loadtxt(dirName + "cat.rcorr", dtype=float, comments='#')
h2oData = np.loadtxt(dirName + "h2o.rcorr", dtype=float, comments='#')

N_an = np.size(anData)
x_an = anData[0:N_an:1, 0]
y_an = anData[0:N_an:1, 1]

x_an /= 1000 											    ## Convert fs -> ps

N_cat = np.size(catData)
x_cat = catData[0:N_cat:1, 0]
y_cat = catData[0:N_cat:1, 1]

x_cat /= 1000 											    ## Convert fs -> ps

N_h2o = np.size(h2oData)
x_h2o = h2oData[0:N_h2o:1, 0]
y_h2o = h2oData[0:N_h2o:1, 1]

x_h2o /= 1000 											    ## Convert fs -> ps


### Plotting FNEMD Results ###
fnemdData = np.loadtxt(dirName + "FNEMD.txt", dtype=float, comments='#')

N_fnemd = np.size(fnemdData)
Ez = fnemdData[0:N_fnemd:1, 0]
Jc_anion = fnemdData[0:N_fnemd:1, 1]
Jc_cation = fnemdData[0:N_fnemd:1, 2]
Jc_total = fnemdData[0:N_fnemd:1, 3]


Ez_avg = getAverages(Ez, 5) * 10
Jc_anion_avg = getAverages(Jc_anion, 5) * 1e7
Jc_cation_avg = getAverages(Jc_cation, 5) * 1e7
Jc_total_avg = getAverages(Jc_total, 5) * 1e7


## Ordinary Least Squares ##
ols_model_an = sm.OLS(Jc_anion_avg, Ez_avg)
ols_results_an = ols_model_an.fit()

ols_model_cat = sm.OLS(Jc_cation_avg, Ez_avg)
ols_results_cat = ols_model_cat.fit()

ols_model_tot = sm.OLS(Jc_total_avg, Ez_avg)
ols_results_tot = ols_model_tot.fit()


### Plotting Lennard-Jones Parameters
r = np.linspace(1e-9, 10, 10000)

## [ sigma (Ang), epsilon (kcal/mol) ] ##
LithiumParameters  = [ 2.337, 0.1601 ]
SodiumParameters   = [ 2.876, 0.1247 ]
CalciumParameters  = [ 3.019, 0.1247 ]
ChlorineParameters = [ 3.785, 0.1247 ]

V_Li = lennardJones(*LithiumParameters, r)
V_Na = lennardJones(*SodiumParameters, r)
V_Cl = lennardJones(*ChlorineParameters, r)
V_Ca = lennardJones(*CalciumParameters, r)


### Plotting ###
plt.figure(1)
plt.plot(x_an, y_an, color="tab:green", label= "MSD Cl$^-$")
plt.plot(x_cat, y_cat, color="tab:orange", label= "MSD Na$^+$")
plt.plot(x_h2o, y_h2o, color="tab:blue", label= "MSD H$_2$O")

plt.title("Mean Squared Displacement of Relevant Species")
plt.xlabel("Time (ps)")
plt.ylabel("$\\langle|r(t) - r(0)|^2 \\rangle$ ($\\AA^2$)")
plt.xlim(0)
plt.ylim(0)
plt.legend()
plt.savefig(dirName + "rcorr_plots.pdf")


plt.figure(2)
plt.plot(Ez_avg, Jc_anion_avg, 'o', color="tab:green", label="J$_c$ Cl$^-$")
plt.plot(Ez_avg, ols_results_an.fittedvalues, color="tab:green")
plt.plot(Ez_avg, Jc_cation_avg, 'o', color="tab:orange", label="J$_c$ Na$^+$")
plt.plot(Ez_avg, ols_results_cat.fittedvalues, color="tab:orange")
plt.plot(Ez_avg, Jc_total_avg, 'o', color="tab:blue", label="J$_c$ Total")
plt.plot(Ez_avg, ols_results_tot.fittedvalues, color="tab:blue")

plt.title("FNEMD Calculations of Linear Response Region for NaCl")
plt.xlabel("$E_z$ (dV/$\\AA$)")
plt.ylabel("Current Density ( 1$\\times 10^{-7}$ e/$\\AA^2$/fs)")
plt.legend()
plt.savefig(dirName + "FNEMD_plots.pdf")


plt.figure(3)
plt.plot(r, V_Li, label="Li$^+$")
plt.plot(r, V_Na, label="Na$^+$")
plt.plot(r, V_Cl, label="Cl$^-$")
plt.plot(r, V_Ca, label="Ca$^{2+}$")

plt.title("Lennard Jones Parameters for Relevant Ions")
plt.xlabel("$r$ ($\\AA$)")
plt.ylabel("$V_{LJ}$ (kcal/mol)")
plt.xlim(2, 10)
plt.ylim(-0.2, 0.2)
plt.legend()
plt.savefig(dirName + "LennardJones_plots.pdf")
