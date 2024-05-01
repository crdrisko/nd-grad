#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: plotMembraneResults.py - Version 1.0.0
# Author: crdrisko
# Date: 04/23/2024-09:03:42
# Description:

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as plticker
from matplotlib import rc
from scipy.optimize import curve_fit
from collections import defaultdict
from os import path
from decimal import Decimal

area = 41.0 * 42.0       # Ang^2
temperature = 293.15     # K
idealGasConstant = 8.314 # J/mol/K

### Functions ###
def unzipDictionary(input):
    x, y = zip(*sorted(input.items()))

    x = list(x)
    y = list(y)

    return x, y

def exponential(x, a0, a1):
  return a0 * (1 - np.e**(-x / a1))

def linearThroughZero(x, a0):
  return a0 * x

def linear(x, a0, a1):
  return a0 * x + a1

def getAverageDeltaP(exchangeTime):
    pressures = {}
    counts = {}

    DeltaPs = defaultdict(list)

    for seed in range(5, 10):
        fileName = "/Users/crdrisko/Desktop/SPF/SPF-Results/Graphene/WaterStitch/spf" + str(exchangeTime) + "_ps/stitch" + str(seed) + ".txt"

        if (path.isfile(fileName)):
            data = np.loadtxt(fileName, delimiter=',', comments='#')

            N = np.size(data)
            indicies   = data[0:N:1, 0] / 10
            DeltaP     = (data[0:N:1, 1] / (area)) * (1e30 * 4184) / (6.022e23 * 1e5) # Convert kcal/mol/Ang^3 -> bar

        for i in range(0, np.size(indicies)):
            if (counts.get(indicies[i]) == None):
                pressures[indicies[i]] = 0
                counts[indicies[i]] = 0

            pressures[indicies[i]] += DeltaP[i]
            counts[indicies[i]] += 1

            DeltaPs[indicies[i]].append(DeltaP[i])

    for key in pressures:
        pressures[key] /= counts[key]

    errors = {}

    for key in DeltaPs:
        for i in range(0, len(DeltaPs[key])):
            if (i == 0):
                errors[key] = 0
            errors[key] += (DeltaPs[key][i] - pressures[key])**2

    for key in pressures:
        errors[key] = np.sqrt(np.abs(errors[key]) / counts[key])

    return pressures, errors

def getAverageDeltaPi(exchangeTime):
    osmoticPressures = {}
    counts = {}
    fluxes = {}

    DeltaPis = defaultdict(list)

    for seed in range(5, 10):
        fileName = "/Users/crdrisko/Desktop/SPF/SPF-Results/Graphene/WaterStitch/spf" + str(exchangeTime) + "_ps/stitch" + str(seed) + ".csv"

        if (path.isfile(fileName)):
            data = np.loadtxt(fileName, delimiter=',', comments='#')

            N = np.size(data)
            indicies   = data[0:N:1, 0] / 10
            Jp_applied = data[0:N:1, 1]
            Jp_actual  = data[0:N:1, 2] / 1e-8
            DeltaPi     = (data[0:N:1, 3] * temperature * idealGasConstant) * (1000 * 1e-5)

        for i in range(0, np.size(indicies)):
            if (counts.get(indicies[i]) == None):
                osmoticPressures[indicies[i]] = 0
                counts[indicies[i]] = 0
                fluxes[indicies[i]] = 0

            osmoticPressures[indicies[i]] += DeltaPi[i]
            counts[indicies[i]] += 1
            fluxes[indicies[i]] += Jp_actual[i]

            DeltaPis[indicies[i]].append(DeltaPi[i])

    for key in osmoticPressures:
        osmoticPressures[key] /= counts[key]
        fluxes[key] /= counts[key]

    errors = {}

    for key in DeltaPis:
        for i in range(0, len(DeltaPis[key])):
            if (i == 0):
                errors[key] = 0
            errors[key] += (DeltaPis[key][i] - osmoticPressures[key])**2

    for key in osmoticPressures:
        errors[key] = np.sqrt(np.abs(errors[key]) / counts[key])

    return osmoticPressures, errors, fluxes

def getPlots(exchangeTime, lastFluxes, averages, errors, count):
    x, y = unzipDictionary(averages)
    errors_x, sigma_y = unzipDictionary(errors)

    x.insert(0, 0)
    y.insert(0, 0)
    sigma_y.insert(0, 0)

    popt, pcov = curve_fit(exponential, x, y)

    stdDev = np.sqrt(np.diag(pcov))

    results = popt[0]
    errorsInResults = stdDev[0]

    axes[count][0].plot(x, exponential(np.array(x), *popt), color=colors[exchangeTime],
                    label="  %0.2f$\\times 10^{-8}$      $\\rightarrow$ %9.3f    %10.0f" % (lastFluxes[int((exchangeTime - 10) / 2)], popt[1], np.round(popt[0], count - 1)))
    axes[count][0].errorbar(x, y, sigma_y,
                        marker=markers[exchangeTime], markeredgewidth = 1.5, fillstyle = 'full', markerfacecolor = 'w', linestyle='none', color=colors[exchangeTime])
    # axes[1][0].axhline(popt[0], linestyle='--', color=colors[exchangeTime])

    axes[count][1].errorbar(lastFluxes[int((exchangeTime - 10) / 2)], results, errorsInResults,
                 marker=markers[exchangeTime], markeredgewidth = 1.5, fillstyle = 'full', markerfacecolor = 'w', linestyle='none', color=colors[exchangeTime])

    return results, errorsInResults


### Main Code ###
colors = {8: '#000000', 10: '#FF0000', 12: '#008B00', 14: '#0000FF'}
markers = {8: "o", 10: "s", 12: "D", 14: "^"}

lastFluxes         = np.empty(3)
deltaPInf          = np.empty(3)
errorsInDeltaPInf  = np.empty(3)
deltaPiInf         = np.empty(3)
errorsInDeltaPiInf = np.empty(3)

with plt.rc_context(fname='nd-grad/nd-research/scripts/spfResultParsing/custom.rc'):
    fig, axes = plt.subplots(2, 2, figsize=(10, 8), sharey = False)

for exchangeTime in range(10, 16, 2):
    averagesPi, errorsPi, fluxes = getAverageDeltaPi(exchangeTime)
    averagesP, errorsP = getAverageDeltaP(exchangeTime)

    x2, y2 = zip(*sorted(fluxes.items()))
    lastFluxes[int((exchangeTime - 10) / 2)] =  y2[-1]

    results_P, errorInResults_P = getPlots(exchangeTime, lastFluxes, averagesP, errorsP, 0)

    deltaPInf[int((exchangeTime - 10) / 2)] = results_P
    errorsInDeltaPInf[int((exchangeTime - 10) / 2)] = errorInResults_P

    results_Pi, errorInResults_Pi = getPlots(exchangeTime, lastFluxes, averagesPi, errorsPi, 1)

    deltaPiInf[int((exchangeTime - 10) / 2)] = results_Pi
    errorsInDeltaPiInf[int((exchangeTime - 10) / 2)] = errorInResults_Pi

## Calculate Permeabilities
popt2_P, pcov2_P = curve_fit(linearThroughZero, lastFluxes, deltaPInf)
stdDev2_P = np.sqrt(np.diag(pcov2_P))
axes[0][1].plot(lastFluxes, linearThroughZero(lastFluxes, *popt2_P), color='k')
axes[0][1].set_zorder(-1)

popt2_Pi, pcov2_Pi = curve_fit(linearThroughZero, lastFluxes, deltaPiInf)
stdDev2_Pi = np.sqrt(np.diag(pcov2_Pi))
axes[1][1].plot(lastFluxes, linearThroughZero(lastFluxes, *popt2_Pi), color='k')
axes[1][1].set_zorder(-1)

conversionFactor = ((18.016 * 0.001 * 1e15 * 3600) / (6.022e23)) * 1e-8 

A_wd = (1 / (popt2_P[0] - popt2_Pi[0])) * (conversionFactor * 2 * area) 

stdDev_A_wd = np.sqrt((stdDev2_P[0]**2 + stdDev2_Pi[0]**2)) * (A_wd**2 / (conversionFactor * 2 * area))

print("(%0.4f +/- %0.4f) x 10^-15 L / hr-bar-pore" %(A_wd / 1e-15, stdDev_A_wd / 1e-15))

for poreDensity in [1.7e13, 2.5e11]:
    print("%5.1f x 10^11 cm^-2: (%0.4f +/- %0.4f) L / m^2-hr-bar" %(poreDensity / 1.0e11, A_wd * poreDensity * 100**2, stdDev_A_wd * poreDensity * 100**2))

## X-Axis Parameters for axes[0][0]
axes[0][0].set_xlim(0.0, 5.0)
axes[0][0].xaxis.set_major_locator(plticker.MultipleLocator(1))
axes[0][0].xaxis.set_minor_locator(plticker.MultipleLocator(0.5))
axes[0][0].xaxis.set_ticklabels("")
axes[0][0].xaxis.tick_top()
axes[0][0].xaxis.set_ticks_position('both')

## Y-Axis Parameters for axes[0][0]
axes[0][0].set_ylim(0, 2000)
axes[0][0].set_ylabel("$\\Delta P$ (bar)")
axes[0][0].yaxis.set_major_locator(plticker.MultipleLocator(500))
axes[0][0].yaxis.set_minor_locator(plticker.MultipleLocator(250))

## X-Axis Parameters for axes[0][1]
axes[0][1].set_xlim(2.0, 3.0)
axes[0][1].xaxis.set_major_locator(plticker.MultipleLocator(0.2))
axes[0][1].xaxis.set_minor_locator(plticker.MultipleLocator(0.1))
axes[0][1].xaxis.set_ticklabels("")
axes[0][1].xaxis.set_label_position('top')
axes[0][1].xaxis.tick_top()
axes[0][1].xaxis.set_ticks_position('both')

## Y-Axis Parameters for axes[0][1]
axes[0][1].set_ylim(axes[0][0].get_ylim())
axes[0][1].set_ylabel("$\\Delta P_\\infty$ (bar)")
axes[0][1].yaxis.set_major_locator(plticker.MultipleLocator(500))
axes[0][1].yaxis.set_minor_locator(plticker.MultipleLocator(250))
axes[0][1].yaxis.set_label_position('right')
axes[0][1].yaxis.tick_right()
axes[0][1].yaxis.set_ticks_position('both')

## X-Axis Parameters for axes[1][0]
axes[1][0].set_xlim(0.0, 5.0)
axes[1][0].set_xlabel("Sample Time (ns)")
axes[1][0].xaxis.set_major_locator(plticker.MultipleLocator(1))
axes[1][0].xaxis.set_minor_locator(plticker.MultipleLocator(0.5))
axes[1][0].xaxis.set_label_position('bottom')

## Y-Axis Parameters for axes[1][0]
axes[1][0].set_ylim(0, 90)
axes[1][0].set_ylabel("$\\Delta \\Pi$ (bar)")
axes[1][0].yaxis.set_major_locator(plticker.MultipleLocator(20))
axes[1][0].yaxis.set_minor_locator(plticker.MultipleLocator(10))

## X-Axis Parameters for axes[1][1]
axes[1][1].set_xlim(axes[0][1].get_xlim())
axes[1][1].set_xlabel("J$_p$ ($\\times 10^{-8}$ molecules $\\AA^{-2}$ fs$^{-1}$)")
axes[1][1].xaxis.set_major_locator(plticker.MultipleLocator(0.2))
axes[1][1].xaxis.set_minor_locator(plticker.MultipleLocator(0.1))

## Y-Axis Parameters for axes[1][1]
axes[1][1].set_ylim(axes[1][0].get_ylim())
axes[1][1].set_ylabel("$\\Delta \\Pi_\\infty$ (bar)")
axes[1][1].yaxis.set_major_locator(plticker.MultipleLocator(20))
axes[1][1].yaxis.set_minor_locator(plticker.MultipleLocator(10))
axes[1][1].yaxis.set_label_position('right')
axes[1][1].yaxis.tick_right()
axes[1][1].yaxis.set_ticks_position('both')

# fig.legend(edgecolor="k", fontsize=12, fancybox=False, framealpha = 1.0,
#            title_fontsize = 12, bbox_to_anchor=[0.5, 0.3], loc='center', facecolor='white', alignment = 'left',
#            title="J$_p$ (molecules $\\AA^{-2}$ fs$^{-1}$)    $\\tau_{\\mathrm{relax}}$ (ns)    $\\Delta c_{\\infty}$ (M)").get_frame().set_linewidth(1.5)

axes[0][0].legend(edgecolor="k", fontsize=10, fancybox=False, framealpha = 1.0,
           title_fontsize = 10, bbox_to_anchor=[1.0, 0.2], loc='center', facecolor='white', alignment = 'left',
           title="J$_p$ (molecules $\\AA^{-2}$ fs$^{-1}$)    $\\tau_{\\mathrm{relax}}$ (ns)    $\\Delta P_{\\infty}$ (bar)").get_frame().set_linewidth(1.5)

axes[1][0].legend(edgecolor="k", fontsize=10, fancybox=False, framealpha = 1.0,
           title_fontsize = 10, bbox_to_anchor=[1.0, 0.2], loc='center', facecolor='white', alignment = 'left',
           title="J$_p$ (molecules $\\AA^{-2}$ fs$^{-1}$)    $\\tau_{\\mathrm{relax}}$ (ns)    $\\Delta \\Pi_{\\infty}$ (bar)").get_frame().set_linewidth(1.5)

rc('pdf', fonttype=42)
plt.savefig("/Users/crdrisko/Desktop/SPF/SPF-Results/Graphene/WaterStitch/WaterStitch.pdf")
plt.show()

