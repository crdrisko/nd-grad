#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (c) 2019-2025 Cody R. Drisko. All rights reserved.
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

### Classes and Functions ###
class ValueAndError:
    def __init__(self, value, error):
        self.value = value
        self.error = error

    def unzipDictionary(self):
        x, y = zip(*sorted(self.value.items()))
        error_x, error_y = zip(*sorted(self.error.items()))

        return np.array(x), np.array(y), np.array(error_y)

def exponential(x, a0, a1):
    return a0 * (1 - np.exp(-x / a1))

def calcError(sample, average, counts):
    errors = {}

    for key in sample:
        for i in range(0, len(sample[key])):
            if (i == 0):
                errors[key] = 0
            errors[key] += (sample[key][i] - average[key])**2

    for key in sample:
        errors[key] = np.sqrt(np.abs(errors[key]) / counts[key])

    return errors 

def getLabel(pore: str):
    if (len(pore) > 3):
        label = '{poreSize: <{width}}'.format(poreSize=pore, width=5)
    else:
        label = '{poreSize: <{width}}'.format(poreSize=pore, width=7)
    
    return label

def getAverageDeltaConc(pore: str):
    counts           = {}
    fluxes           = {}
    concs_Cation     = {}
    concs_Anion      = {}
    rejection_Cation = {}
    rejection_Anion  = {}

    Applied_Fluxes    = defaultdict(list)
    DeltaCs_Cation    = defaultdict(list)
    DeltaCs_Anion     = defaultdict(list)
    Rejections_Cation = defaultdict(list)
    Rejections_Anion  = defaultdict(list)

    for seed in range(5, 10):
        fileName = "/Volumes/Research/Charge/NaCl/spf120_ps/" + pore + "/RNEMD" + str(seed) + ".csv"

        if (path.isfile(fileName)):
            data = np.loadtxt(fileName, delimiter=',', comments='#')

            N = np.size(data)
            indicies   = data[0:N:1, 0] * 600 / 1000
            Jp_applied = data[0:N:1, 1]
            Jp_actual  = data[0:N:1, 2]
            conc_Na_B  = data[0:N:1, 3]
            conc_Na_A  = data[0:N:1, 4]
            conc_Na    = data[0:N:1, 5]
            conc_Cl_B  = data[0:N:1, 6]
            conc_Cl_A  = data[0:N:1, 7]
            conc_Cl    = data[0:N:1, 8]
            conc_O     = data[0:N:1, 9]
            conc_H     = data[0:N:1, 10]

        for i in range(0, np.size(indicies)):
            if (counts.get(indicies[i]) == None):
                concs_Cation[indicies[i]] = 0
                concs_Anion[indicies[i]] = 0
                counts[indicies[i]] = 0
                fluxes[indicies[i]] = 0
                rejection_Cation[indicies[i]] = 0
                rejection_Anion[indicies[i]] = 0

            concs_Cation[indicies[i]] += conc_Na[i]
            concs_Anion[indicies[i]] += conc_Cl[i]
            counts[indicies[i]] += 1
            fluxes[indicies[i]] += Jp_actual[i]

            R_cation = 1 - (conc_Na_A[i] / conc_Na_B[i])
            R_anion = 1 - (conc_Cl_A[i] / conc_Cl_B[i])

            rejection_Cation[indicies[i]] += R_cation
            rejection_Anion[indicies[i]] += R_anion

            DeltaCs_Cation[indicies[i]].append(conc_Na[i])
            DeltaCs_Anion[indicies[i]].append(conc_Cl[i])

            Rejections_Cation[indicies[i]].append(R_cation)
            Rejections_Anion[indicies[i]].append(R_anion)

            Applied_Fluxes[indicies[i]].append(Jp_actual[i])

    for key in fluxes:
        fluxes[key] /= counts[key]
        concs_Cation[key] /= counts[key]
        concs_Anion[key] /= counts[key]
        rejection_Cation[key] /= counts[key]
        rejection_Anion[key] /= counts[key]

    Fluxes           = ValueAndError(fluxes, calcError(Applied_Fluxes, fluxes, counts))
    Concs_Cation     = ValueAndError(concs_Cation, calcError(DeltaCs_Cation, concs_Cation, counts))
    Concs_Anion      = ValueAndError(concs_Anion, calcError(DeltaCs_Anion, concs_Anion, counts))
    Rejection_Cation = ValueAndError(rejection_Cation, calcError(Rejections_Cation, rejection_Cation, counts))
    Rejection_Anion  = ValueAndError(rejection_Anion, calcError(Rejections_Anion, rejection_Anion, counts))

    return Fluxes, Concs_Cation, Concs_Anion, Rejection_Cation, Rejection_Anion

def getConcentrationPlots(pore: str, concentrations: ValueAndError, count: int):
    x, y, errors_y = concentrations.unzipDictionary()

    # Shift points before we add a point at (0, 0)
    for i in range(0, len(x)):
        x[i] = x[i] - 0.3

    np.concatenate([[0], x])
    np.concatenate([[0], y])
    np.concatenate([[0], errors_y])

    popt, pcov = curve_fit(exponential, x, y)

    stdDev = np.sqrt(np.diag(pcov))

    result = ValueAndError(popt[0], stdDev[0])

    axes1[count].plot(x, exponential(np.array(x), *popt), color=colors[pore],
                      label="%s   $\\rightarrow$ %9.3f         %0.02f" % (getLabel(pore), popt[1], popt[0]))
    axes1[count].errorbar(x, y, errors_y, capsize=3,
                          marker=markers[pore], markeredgewidth = 1.5, fillstyle = 'full', markerfacecolor = 'w', linestyle='none', color=colors[pore])

    return result

def getFluxPlots(pore: str, fluxes: ValueAndError):
    x, y, errors_y = fluxes.unzipDictionary()

    # Shift points
    for i in range(0, len(x)):
        x[i] = x[i] - 0.3

    axes2.errorbar(x, np.array(y) * 1e9, np.array(errors_y) * 1e9, capsize=3,
                   label="%s" % (getLabel(pore)), marker=markers[pore], markeredgewidth = 1.5, fillstyle = 'full', markerfacecolor = 'w', linestyle='none', color=colors[pore])
    axes2.axhline(y[0] * 1e9, linestyle='--', color='k')

def getPermeabilityPlots(pore: str, flux: ValueAndError, concentration: ValueAndError, count: int):
    flux_x, flux_y, flux_errors_y = flux.unzipDictionary()
    concentration_x, concentration_y, concentration_errors_y = concentration.unzipDictionary()

    ConcentrationResults = getConcentrationPlots(pore, concentration, count)

    ## Calculate Permeabilities
    conversionFactor = (1e20 * 1e15 * 3600) / 6.022e23 * 1e-6
    # conversionFactor = (1e20 * 1e15) / 6.022e23 / 1000

    # Shift points
    for i in range(0, len(flux_x)):
        flux_x[i] = flux_x[i] - 0.3

    B_sd  = flux_y / concentration_y * conversionFactor
    stdDev_B_sd = np.sqrt( ((1 / concentration_y)**2 * flux_errors_y**2) + ((flux_y / concentration_y**2)**2 * concentration_errors_y**2)) * conversionFactor

    axes3[0][count].errorbar(flux_x, B_sd, stdDev_B_sd, capsize=3,
                             label="%s" % (getLabel(pore)), marker=markers[pore], markeredgewidth = 1.5, fillstyle = 'full', markerfacecolor = 'w', linestyle='none', color=colors[pore])

    temp_B_sd = (flux_y[-1] / ConcentrationResults.value)  * conversionFactor
    temp_stdDev_B_sd = np.sqrt( ((1 / ConcentrationResults.value)**2 * flux_errors_y[-1]**2) + ((flux_y[-1] / ConcentrationResults.value**2)**2 * ConcentrationResults.error**2))  * conversionFactor

    poreName = '{poreSize: <{width}}'.format(poreSize=pore, width=5)

    if (count == 0):
        print("J_p (Actual) = %0.2f x 10^-9 1 / Ang^2-fs" % (flux_y[-1] * 1e9))
        print("%s Na+: B_sd = (%0.4f +/- %0.4f) x 10^6 L / m^2-hr" % (poreName, temp_B_sd, temp_stdDev_B_sd))
        # print("%s Na+: B_sd = (%0.4f +/- %0.4f) m / s" % (poreName, B_sd[internalCount], stdDev_B_sd[internalCount]))
    else:
        print("      Cl-: B_sd = (%0.4f +/- %0.4f) x 10^6 L / m^2-hr" % (temp_B_sd, temp_stdDev_B_sd))
        # print("      Cl-: B_sd = (%0.4f +/- %0.4f) m / s" % (B_sd[internalCount], stdDev_B_sd[internalCount]))
        print("-----------------------------------------------------------------")

def getRejectionPlots(pore: str, rejections: ValueAndError, count: int):
    x, y, errors_y = rejections.unzipDictionary()

    # Shift points
    for i in range(0, len(x)):
        x[i] = x[i] - 0.3

    axes3[1][count].errorbar(x, y * 100, errors_y * 100, capsize=3,
                             label="%s" % (getLabel(pore)), marker=markers[pore], markeredgewidth = 1.5, fillstyle = 'full', markerfacecolor = 'w', linestyle='none', color=colors[pore])


### Main Code ###
colors = {"p14x2": '#000000', "p28": '#FF0000', "p22x2":'#008B00', "p40": '#0000FF', "p44": '#FF00FF'}
markers = {"p14x2": "o", "p28": "s", "p22x2": "D", "p40": "^", "p44": "v"}

pores = ["p14x2", "p28", "p22x2", "p40", "p44"]

with plt.rc_context(fname='nd-grad/nd-research/scripts/spfResultParsing/custom.rc'):
    fig1, axes1 = plt.subplots(1, 2, figsize=(12, 6), sharey = True)
    fig2, axes2 = plt.subplots(1, 1, figsize=(8, 6))
    fig3, axes3 = plt.subplots(2, 2, figsize=(12, 9), sharex = True)

for pore in pores:
    Fluxes, Concs_Cation, Concs_Anion, Rejection_Cation, Rejection_Anion = getAverageDeltaConc(pore)

    getFluxPlots(pore, Fluxes)

    getPermeabilityPlots(pore, Fluxes, Concs_Cation, 0)
    getPermeabilityPlots(pore, Fluxes, Concs_Anion, 1)

    getRejectionPlots(pore, Rejection_Cation, 0)
    getRejectionPlots(pore, Rejection_Anion, 1)

## X-Axis Parameters for axes1[0]
axes1[0].set_xlim(0, 12)
axes1[0].set_xlabel("Sample Time (ns)")
axes1[0].xaxis.set_major_locator(plticker.MultipleLocator(2))
axes1[0].xaxis.set_minor_locator(plticker.MultipleLocator(1))
axes1[0].xaxis.set_label_position('bottom')

## Y-Axis Parameters for axes1[0]
axes1[0].set_ylim(-0.25, 2.75)
axes1[0].set_ylabel("$\\Delta$[Na$^+$] (M)")
axes1[0].yaxis.set_major_locator(plticker.MultipleLocator(0.5))
axes1[0].yaxis.set_minor_locator(plticker.MultipleLocator(0.25))

## X-Axis Parameters for axes1[1]
axes1[1].set_xlim(axes1[0].get_xlim())
axes1[1].set_xlabel("Sample Time (ns)")
axes1[1].xaxis.set_major_locator(plticker.MultipleLocator(2))
axes1[1].xaxis.set_minor_locator(plticker.MultipleLocator(1))
axes1[1].xaxis.set_label_position('bottom')

## Y-Axis Parameters for axes1[1]
axes1[1].set_ylim(axes1[0].get_ylim())
axes1[1].set_ylabel("$\\Delta$[Cl$^-$] (M)")
axes1[1].yaxis.set_major_locator(plticker.MultipleLocator(0.5))
axes1[1].yaxis.set_minor_locator(plticker.MultipleLocator(0.25))
axes1[1].yaxis.set_label_position('right')
axes1[1].yaxis.tick_right()
axes1[1].yaxis.set_ticks_position('both')

## X-Axis Parameters for axes2
axes2.set_xlim(0, 12)
axes2.set_xlabel("Sample Time (ns)")
axes2.xaxis.set_major_locator(plticker.MultipleLocator(2))
axes2.xaxis.set_minor_locator(plticker.MultipleLocator(1))
axes2.xaxis.set_label_position('bottom')

## Y-Axis Parameters for axes2
axes2.set_ylim(-0.5, 5.5)
axes2.set_ylabel("J$_p$ ($\\times 10^{-9}$ particles $\\AA^{-2}$ fs$^{-1}$)")
axes2.yaxis.set_major_locator(plticker.MultipleLocator(1))
axes2.yaxis.set_minor_locator(plticker.MultipleLocator(0.5))
axes2.yaxis.set_label_position('left')
axes2.yaxis.tick_left()
axes2.yaxis.set_ticks_position('both')

## X-Axis Parameters for axes3[0][0]
axes3[0][0].set_xlim(0, 12)
axes3[0][0].xaxis.set_major_locator(plticker.MultipleLocator(2))
axes3[0][0].xaxis.set_minor_locator(plticker.MultipleLocator(1))

## Y-Axis Parameters for axes3[0][0]
axes3[0][0].set_ylim(-1, 9)
# axes3[0][0].set_ylim(-0.25, 1.75)
# axes3[0][0].set_ylabel("B$_{\\text{Na}^+}$ (m / s)")
# axes3[0][0].yaxis.set_major_locator(plticker.MultipleLocator(0.5))
# axes3[0][0].yaxis.set_minor_locator(plticker.MultipleLocator(0.25))
axes3[0][0].set_ylabel("B$_{\\text{Na}^+}$ ($\\times 10^{6}$ L m$^{-2}$ hr$^{-1}$)")
axes3[0][0].yaxis.set_major_locator(plticker.MultipleLocator(2))
axes3[0][0].yaxis.set_minor_locator(plticker.MultipleLocator(1))
axes3[0][0].yaxis.set_label_position('left')
axes3[0][0].yaxis.tick_left()
axes3[0][0].yaxis.set_ticks_position('both')

## X-Axis Parameters for axes3[0][1]
axes3[0][1].set_xlim(axes3[0][0].get_xlim())
axes3[0][1].xaxis.set_major_locator(plticker.MultipleLocator(2))
axes3[0][1].xaxis.set_minor_locator(plticker.MultipleLocator(1))

## Y-Axis Parameters for axes3[0][1]
axes3[0][1].set_ylim(axes3[0][0].get_ylim())
# axes3[0][1].set_ylabel("B$_{\\text{Cl}^-}$ (m / s)")
# axes3[0][1].yaxis.set_major_locator(plticker.MultipleLocator(0.5))
# axes3[0][1].yaxis.set_minor_locator(plticker.MultipleLocator(0.25))
axes3[0][1].set_ylabel("B$_{\\text{Cl}^-}$ ($\\times 10^{6}$ L m$^{-2}$ hr$^{-1}$)")
axes3[0][1].yaxis.set_major_locator(plticker.MultipleLocator(2))
axes3[0][1].yaxis.set_minor_locator(plticker.MultipleLocator(1))
axes3[0][1].yaxis.set_label_position('right')
axes3[0][1].yaxis.tick_right()
axes3[0][1].yaxis.set_ticks_position('both')

## X-Axis Parameters for axes3[1][0]
axes3[1][0].set_xlim(axes3[0][0].get_xlim())
axes3[1][0].set_xlabel("Sample Time (ns)")
axes3[1][0].xaxis.set_major_locator(plticker.MultipleLocator(2))
axes3[1][0].xaxis.set_minor_locator(plticker.MultipleLocator(1))
axes3[1][0].xaxis.set_label_position('bottom')

## Y-Axis Parameters for axes3[1][0]
axes3[1][0].set_ylim(-12.5, 112.5)
axes3[1][0].set_ylabel("R$_{\\text{Na}^+}$ (%)")
axes3[1][0].yaxis.set_major_locator(plticker.MultipleLocator(25))
axes3[1][0].yaxis.set_minor_locator(plticker.MultipleLocator(12.5))

## X-Axis Parameters for axes3[1][1]
axes3[1][1].set_xlim(axes3[0][0].get_xlim())
axes3[1][1].set_xlabel("Sample Time (ns)")
axes3[1][1].xaxis.set_major_locator(plticker.MultipleLocator(2))
axes3[1][1].xaxis.set_minor_locator(plticker.MultipleLocator(1))
axes3[1][1].xaxis.set_label_position('bottom')

## Y-Axis Parameters for axes3[1][1]
axes3[1][1].set_ylim(axes3[1][0].get_ylim())
axes3[1][1].set_ylabel("R$_{\\text{Cl}^-}$ (%)")
axes3[1][1].yaxis.set_major_locator(plticker.MultipleLocator(25))
axes3[1][1].yaxis.set_minor_locator(plticker.MultipleLocator(12.5))
axes3[1][1].yaxis.set_label_position('right')
axes3[1][1].yaxis.tick_right()
axes3[1][1].yaxis.set_ticks_position('both')

axes1[0].legend(edgecolor="k", fontsize=10, fancybox=False, framealpha = 1.0,
               title_fontsize = 10, bbox_to_anchor=[0.67, 0.17], loc='center', facecolor='white', alignment = 'left',
               title="       Pore Size      $\\tau_{\\mathrm{relax}}$ (ns)     $\\Delta C_{\\infty}$ (M)").get_frame().set_linewidth(1.5)

axes1[1].legend(edgecolor="k", fontsize=10, fancybox=False, framealpha = 1.0,
               title_fontsize = 10, bbox_to_anchor=[0.67, 0.17], loc='center', facecolor='white', alignment = 'left',
               title="       Pore Size      $\\tau_{\\mathrm{relax}}$ (ns)     $\\Delta C_{\\infty}$ (M)").get_frame().set_linewidth(1.5)

axes2.legend(edgecolor="k", fontsize=10, fancybox=False, framealpha = 1.0,
             title_fontsize = 12, bbox_to_anchor=[0.15, 0.2], loc='center', facecolor='white', alignment = 'left',
             title="    Pore Size").get_frame().set_linewidth(1.5)

axes3[0][0].legend(edgecolor="k", fontsize=10, fancybox=False, framealpha = 1.0,
             title_fontsize = 12, bbox_to_anchor=[0.825, 0.75], loc='center', facecolor='white', alignment = 'left',
             title="    Pore Size").get_frame().set_linewidth(1.5)

axes3[0][1].legend(edgecolor="k", fontsize=10, fancybox=False, framealpha = 1.0,
             title_fontsize = 12, bbox_to_anchor=[0.825, 0.75], loc='center', facecolor='white', alignment = 'left',
             title="    Pore Size").get_frame().set_linewidth(1.5)

axes3[1][0].legend(edgecolor="k", fontsize=10, fancybox=False, framealpha = 1.0,
             title_fontsize = 12, bbox_to_anchor=[0.825, 0.25], loc='center', facecolor='white', alignment = 'left',
             title="    Pore Size").get_frame().set_linewidth(1.5)

axes3[1][1].legend(edgecolor="k", fontsize=10, fancybox=False, framealpha = 1.0,
             title_fontsize = 12, bbox_to_anchor=[0.825, 0.25], loc='center', facecolor='white', alignment = 'left',
             title="    Pore Size").get_frame().set_linewidth(1.5)

rc('pdf', fonttype=42)

fig1.savefig("/Volumes/Research/Charge/NaCl/spf120_ps/conc_spf120_ps.pdf")
fig2.savefig("/Volumes/Research/Charge/NaCl/spf120_ps/flux_spf120_ps.pdf")
fig3.savefig("/Volumes/Research/Charge/NaCl/spf120_ps/results_spf120_ps.pdf")

plt.show()
