#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Fri Mar 15 12:39:44 2019

Author: crdrisko

Description: Lorentz oscillator analysis of reflectivity to reproduce experimental data
    of SiC (Silicon carbide).
    
    Reference: "Infrared Properties of Hexagonal Silicon Carbide" by W.G. Spitzer, D. Kleinman,
         and D. Walsh.
"""

import numpy as np
import matplotlib.pyplot as plt

Reflect_data = np.loadtxt("Fig1_reflect.csv", delimiter=",")         
n_lit_data = np.loadtxt("Fig2_n.csv", delimiter=",")    
k_lit_data = np.loadtxt("Fig2_k.csv", delimiter=",")

N_R = np.size(Reflect_data)
wavelength_R = Reflect_data[0:N_R:1, 0]                             # in micrometers
Reflect = Reflect_data[0:N_R:1, 1]

N_n = np.size(n_lit_data)
wavelength_n = n_lit_data[0:N_n:1, 0]                               # in micrometers
n_lit = n_lit_data[0:N_n:1, 1]

N_k = np.size(k_lit_data)
wavelength_k = k_lit_data[0:N_k:1, 0]                               # in micrometers
k_lit = k_lit_data[0:N_k:1, 1]


##### Parameters #####
w_p     = 9.25e13
w_0     = 4.961e13
gamma   = 3.45e11
eps_inf = 6.7
# By guess and check #

c = 1e8
freq = ((2 * np.pi * c) / (wavelength_R * 1e-6)) 

epsilon_1 = eps_inf + ((w_p**2 * (w_0**2 - freq**2)) / ((w_0**2 - freq**2)**2 \
                        + (gamma * freq)**2))
epsilon_2 = (w_p**2 * gamma * freq) / ((w_0**2 - freq**2)**2 + (gamma * freq)**2)

n = 1/np.sqrt(2) * np.sqrt(epsilon_1 + np.sqrt(epsilon_1**2 + epsilon_2**2))
k = 1/np.sqrt(2) * np.sqrt(-epsilon_1 + np.sqrt(epsilon_1**2 + epsilon_2**2))

Reflect_Lorentz = ((n - 1)**2 + k**2) / ((n + 1)**2 + k**2) * 100


plt.figure("Figure 1")
plt.plot(wavelength_R, Reflect, 'o', label = 'Experimental')
plt.plot(wavelength_R, Reflect_Lorentz, label = 'Theoretical')

plt.xlim(0,22)
plt.ylim(0,100)
plt.xlabel("$\\lambda$ in Microns")
plt.ylabel("Reflectivity in Percent")

plt.legend()

plt.figure("Figure 2")
plt.plot(wavelength_R, k, label = 'k')
plt.plot(wavelength_k, k_lit, label = 'k (literature)')

plt.xlim(8,22)
plt.ylim(0,18)
plt.xlabel("$\\lambda$ in Microns")
plt.ylabel("Extinction Coefficient, (k)")

plt.legend()

plt.figure("Figure 3")
plt.plot(wavelength_R, n, label = 'n')
plt.plot(wavelength_n, n_lit, label = 'n (literature)')

plt.xlim(8,22)
plt.ylim(0,18)
plt.xlabel("$\\lambda$ in Microns")
plt.ylabel("Refractive Index, (n)")

plt.legend()

