#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Sat Mar  2 11:05:15 2019

Author: crdrisko

Description: Calculates and plots the Abs, alpha, n, k, epsilon 1 and 2, and chi 1 and 
    chi 2 from transmissivity and reflectivity data.
"""

import numpy as np
import matplotlib.pyplot as plt

reflect_data = np.loadtxt("Reflect_fig1.csv", delimiter = ",")
trans_data = np.loadtxt("Trans_fig1.csv", delimiter = ",")

N_r = np.size(reflect_data)
wavelength_r = reflect_data[0:N_r:1,0]
reflectivity = reflect_data[0:N_r:1,1]                          # Normal Incidence, theta_i = 0

N_t = np.size(trans_data)
wavelength_t = trans_data[0:N_t:1,0]
transmissivity = trans_data[0:N_t:1,1]

### Absorbance ###

absorbance = np.log(1/(transmissivity/100))

plt.figure("Figure 1")
plt.plot(wavelength_t, absorbance, 'r', label = 'Absorbance')
plt.plot(wavelength_t, transmissivity, 'b', label = 'Transmissivity')
plt.plot(wavelength_r, reflectivity, 'k', label = 'Reflectivity')

plt.legend()
plt.xlabel('Wavelength (nm)')
plt.ylabel('$\\mathcal{R}$, $\\mathcal{T}$, Abs')

### Alpha ###

d = 5.9e-5                                                      # Film length in cm
alpha = (absorbance/d)                                          # alpha in cm^-1      

plt.figure("Figure 2")
plt.plot(wavelength_t, alpha/100000, 'r')

plt.xlabel('Wavelength (nm)')
plt.ylabel('$\\alpha (10^{-5} cm^{-1})$')

### Complex Refractive Index ###

c = 3e17                                                        # Speed of light nm/s
freq = (2 * np.pi * c) / wavelength_t
k = ((alpha / 1e7) * c) / (2 * freq)


n = -(-1-reflectivity+np.sqrt(-k**2*(-1+reflectivity)**2+4*reflectivity)) \
    /(-1+reflectivity) +.75


plt.figure("Figure 3")
plt.plot(wavelength_t, n, 'r', label = 'n')
plt.plot(wavelength_t, k, 'b', label = 'k') 

plt.legend()
plt.xlabel('Wavelength (nm)')
plt.ylabel('n and k')

### Complex Dielectric Constant ###

eps1 = n**2 - k**2
eps2 = 2 * n * k

plt.figure("Figure 4")
plt.plot(wavelength_t, eps1, 'r', label = '$\\epsilon_1$')
plt.plot(wavelength_t, eps2, 'b', label = '$\\epsilon_2$')

plt.legend()
plt.xlabel('Wavelength (nm)')
plt.ylabel('$\\epsilon_1$ and $\\epsilon_2$')

### Complex Susceptibility ###

chi1 = eps1 - 1
chi2 = eps2

plt.figure("Figure 5")
plt.plot(wavelength_t, chi1, 'r', label = '$\\chi_1$')
plt.plot(wavelength_t, chi2, 'b', label = '$\\chi_2$')

plt.legend()
plt.xlabel('Wavelength (nm)')
plt.ylabel('$\\chi_1$ and $\\chi_2$')


