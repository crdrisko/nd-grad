#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Fri Apr 26 21:23:18 2019

Author: crdrisko

Description: A reproduction of Figure 3C in the literature, simulated spectra over a range of electron
     concentrations account for variations in peak spectra.
     
     References: "Direct observation of narrow mid-infrared plasmon linewidths of single metal oxide
          nanocrystals" by Robert W. Johns, Hans A. Bechtel, Evan L. Runnerstrom, Ankit Agrawal,
          Sebastien D. Lounis, and Delia J. Milliron.

"""

import numpy as np
import matplotlib.pyplot as plt
from Data_Import import data_import


def epsilon_p(freq, eps_inf, N_c, Gamma):
     e = 1.60217662e-19                                               # in Cs
     eps_0 = 8.8541878176e-12
     m_eff = .6 * 9.10938356e-31                                      # in C^2 N^-1 m^-2
     w_p = np.sqrt(((N_c/1e-6) * e**2) / (eps_0 * m_eff))             # in Hz
     return eps_inf - (w_p**2)/(freq**2 + 1j*freq*Gamma)

def C_abs(Volume, k, epsilon_H, epsilon_p):
     return 3 * Volume * k * np.sqrt(epsilon_H) * np.imag((epsilon_p - epsilon_H)/(epsilon_p \
                       + 2*epsilon_H))


### Finding the Average Particle Size from Histogram ###
     
diameter, relativeFreq = data_import("ptclSize.csv",',')

diameter = np.round(diameter, decimals=0)
relativeFreq = np.round(relativeFreq, decimals=0)

weight = diameter * relativeFreq
averageDiameter = np.round(np.sum(weight) / np.sum(relativeFreq), decimals=0)


### Calculating the absorption cross section ###

c = 3e10
energy = np.linspace(4000, 1000, 3001)
freq = 2*np.pi * c * energy
k = 2*np.pi * energy

blue_eps = epsilon_p(freq, 3.7, 2.17e20, 898.69 * 2 * np.pi * c)
black_eps = epsilon_p(freq, 3.7, 2.9e20, 898.69 * 2 * np.pi * c)
red_eps = epsilon_p(freq, 3.7, 3.63e20, 898.69 * 2 * np.pi * c)

Volume = ((4/3) * np.pi * (averageDiameter/2)**3) * 1e-21             # in cm^3

blue_C_abs = C_abs(Volume, k, 1, blue_eps)
black_C_abs = C_abs(Volume, k, 1, black_eps)
red_C_abs = C_abs(Volume, k, 1, red_eps)


### Normalizing the peak heights to the maximum of the black plot ###

blueMax = np.max(blue_C_abs)
blackMax = np.max(black_C_abs)
redMax = np.max(red_C_abs)

alpha_red = blackMax/redMax
alpha_blue = blackMax/blueMax


### Plotting ###

plt.plot(energy, blue_C_abs * 1e12 * alpha_blue, 'b')
plt.plot(energy, black_C_abs * 1e12, 'k')
plt.plot(energy, red_C_abs * 1e12 * alpha_red, 'r')

plt.xlabel("Energy ($cm^{-1}$)")
plt.ylabel("Extinction (a.u.)")
plt.xlim(4000, 1000)
plt.ylim(0, 1.0)