#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Tue Feb 19 09:36:19 2019

Author: crdrisko

Description: Epsilon 1 and 2 values for Soda Lime Glass, Silicon, and Chromium.
    n and k values were extracted from provided plots and manually cut to 
    equivalently sized arrays. References below.
"""

import numpy as np
import matplotlib.pyplot as plt

#%% Soda Lime Glass (Insulator)

### Refractive Index ###

SLG_n_data = np.loadtxt("n_glass.csv", delimiter=",", skiprows=1)
SLG_k_data = np.loadtxt("k_glass.csv", delimiter=",", skiprows=1)

N_n_SLG = np.size(SLG_n_data)
wavelength_n_SLG = SLG_n_data[0:N_n_SLG:1, 0]
n_values_SLG = SLG_n_data[0:N_n_SLG:1, 1]

N_k_SLG = np.size(SLG_k_data)
wavelength_k_SLG = SLG_k_data[0:N_k_SLG:1, 0]
k_values_SLG = SLG_k_data[0:N_k_SLG:1, 1]

plt.figure('Figure 1')
plt.plot(wavelength_n_SLG, n_values_SLG, color='r', label='n')
plt.plot(wavelength_k_SLG, k_values_SLG, color='b', label='k')

plt.legend()
plt.xlabel('Wavelength ($\\mu m$)')
plt.ylabel('n and k')
plt.title('Frequency-dependent n and k values for Soda Lime Glass')

### Dielectric Constant ###

eps1_SLG = n_values_SLG**2 - k_values_SLG**2
eps2_SLG = 2 * n_values_SLG * k_values_SLG

plt.figure('Figure 2')
plt.plot(wavelength_n_SLG, eps1_SLG, 'r', label='$\\epsilon_1$') 
plt.plot(wavelength_k_SLG, eps2_SLG, 'b', label='$\\epsilon_2$')

plt.legend()
plt.xlabel('Wavelength ($\\mu m$)')
plt.ylabel('$\\epsilon_1$ and $\\epsilon_2$')
plt.title('Frequency-dependent $\\epsilon_1$ and $\\epsilon_2$ values for Soda Lime Glass')

#%% Si (Semiconductor)

### Refractive Index ###

Si_data = np.loadtxt("Si_refract.csv", delimiter=",", skiprows=1)

N_Si = np.size(Si_data)
wavelength_Si = Si_data[0:N_Si:1, 0]
n_values_Si = Si_data[0:N_Si:1, 1]
k_values_Si = Si_data[0:N_Si:1, 2]

plt.figure('Figure 1')
plt.plot(wavelength_Si, n_values_Si, color='r', label='n')
plt.plot(wavelength_Si, k_values_Si, color='b', label='k')

plt.legend()
plt.xlabel('Wavelength ($\\mu m$)')
plt.ylabel('n and k')
plt.title('Frequency-dependent n and k values for Silicon')

### Dielectric Constant ###

eps1_Si = n_values_Si**2 - k_values_Si**2
eps2_Si = 2 * n_values_Si * k_values_Si

plt.figure('Figure 2')
plt.plot(wavelength_Si, eps1_Si, 'r', label='$\\epsilon_1$') 
plt.plot(wavelength_Si, eps2_Si, 'b', label='$\\epsilon_2$')

plt.legend()
plt.xlabel('Wavelength ($\\mu m$)')
plt.ylabel('$\\epsilon_1$ and $\\epsilon_2$')
plt.title('Frequency-dependent $\\epsilon_1$ and $\\epsilon_2$ values for Silicon')

#%% Cr (Metal)

### Refractive Index ###

Cr_data = np.loadtxt("Cr_refract.csv", delimiter=",", skiprows=1)

N_Cr = np.size(Cr_data)
wavelength_Cr = Cr_data[0:N_Cr:1, 0]
n_values_Cr = Cr_data[0:N_Cr:1, 1]
k_values_Cr = Cr_data[0:N_Cr:1, 2]

plt.figure('Figure 1')
plt.plot(wavelength_Cr, n_values_Cr, color='r', label='n')
plt.plot(wavelength_Cr, k_values_Cr, color='b', label='k')

plt.legend()
plt.xlabel('Wavelength ($\\mu m$)')
plt.ylabel('n and k')
plt.title('Frequency-dependent n and k values for Chromium')

### Dielectric Constant ###

eps1_Cr = n_values_Cr**2 - k_values_Cr**2
eps2_Cr = 2 * n_values_Cr * k_values_Cr

plt.figure('Figure 2')
plt.plot(wavelength_Cr, eps1_Cr, 'r', label='$\\epsilon_1$') 
plt.plot(wavelength_Cr, eps2_Cr, 'b', label='$\\epsilon_2$')

plt.legend()
plt.xlabel('Wavelength ($\\mu m$)')
plt.ylabel('$\\epsilon_1$ and $\\epsilon_2$')
plt.title('Frequency-dependent $\\epsilon_1$ and $\\epsilon_2$ values for Chromium')

#############################################################################################
#                                                                                           #
#               References: All data taken from: https://refractiveindex.info               #
#    Insulator:                                                                             #
#        M. Rubin. Optical properties of soda lime silica glasses,                          # 
#        Sol. Energy Mater. 12, 275-288 (1985)                                              #
#   Semiconductor:                                                                          #
#        D. E. Aspnes and A. A. Studna. Dielectric functions and optical parameters         #
#        of Si, Ge, GaP, GaAs, GaSb, InP, InAs, and InSb from 1.5 to 6.0 eV,                #
#        Phys. Rev. B 27, 985-1009 (1983)                                                   #
#    Metal:                                                                                 #
#        P. B. Johnson and R. W. Christy. Optical constants of transition metals:           #
#        Ti, V, Cr, Mn, Fe, Co, Ni, and Pd, Phys. Rev. B 9, 5056-5070 (1974)                #
#                                                                                           #
#############################################################################################