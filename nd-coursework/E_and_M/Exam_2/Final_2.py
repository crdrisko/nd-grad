#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Fri Apr 26 20:21:07 2019

Author: crdrisko

Description: Curve fitting of the provided reflectance data for MgO. The optical constants and dielectric
    functions are plotted from the resulting fit of the reflectance.

"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from Data_Import import data_import

###########################################          Functions          ###########################################
     
def n_function(epsilon_1, epsilon_2):
     return (1/np.sqrt(2)) * np.sqrt((epsilon_1) + np.sqrt((epsilon_1)**2 + (epsilon_2)**2))

def k_function(epsilon_1, epsilon_2):
     return (1/np.sqrt(2)) * np.sqrt(-(epsilon_1) + np.sqrt((epsilon_1)**2 + (epsilon_2)**2))

def epsilon(freq, epsilon_inf, w_p, w_0, gamma):
     return epsilon_inf + w_p**2 * ((w_0**2 - freq**2)/((w_0**2 - freq**2)**2 + (gamma*freq)**2)), \
            (w_p**2 * gamma * freq)/((w_0**2 - freq**2)**2 + (gamma*freq)**2)           

def Reflectance(freq, epsilon_inf, w_p, w_0, gamma):
     return ((((1/np.sqrt(2)) * np.sqrt((epsilon_inf + w_p**2 * ((w_0**2 - freq**2)/((w_0**2 - freq**2)**2         \
          + (gamma*freq)**2))) + np.sqrt((epsilon_inf + w_p**2 * ((w_0**2 - freq**2)/((w_0**2 - freq**2)**2        \
          + (gamma*freq)**2)))**2 + ((w_p**2 * gamma * freq)/((w_0**2 - freq**2)**2 + (gamma*freq)**2))**2)))      \
          - 1)**2 + ((1/np.sqrt(2)) * np.sqrt(-(epsilon_inf + w_p**2 * ((w_0**2 - freq**2)/((w_0**2 - freq**2)**2  \
          + (gamma*freq)**2))) + np.sqrt((epsilon_inf + w_p**2 * ((w_0**2 - freq**2)/((w_0**2 - freq**2)**2        \
          + (gamma*freq)**2)))**2 + ((w_p**2 * gamma * freq)/((w_0**2 - freq**2)**2 + (gamma*freq)**2))**2)))**2)  \
          /((((1/np.sqrt(2)) * np.sqrt((epsilon_inf + w_p**2 * ((w_0**2 - freq**2)/((w_0**2 - freq**2)**2          \
          + (gamma*freq)**2))) + np.sqrt((epsilon_inf + w_p**2 * ((w_0**2 - freq**2)/((w_0**2 - freq**2)**2        \
          + (gamma*freq)**2)))**2 + ((w_p**2 * gamma * freq)/((w_0**2 - freq**2)**2 + (gamma*freq)**2))**2)))      \
          + 1)**2 + ((1/np.sqrt(2)) * np.sqrt(-(epsilon_inf + w_p**2 * ((w_0**2 - freq**2)/((w_0**2 - freq**2)**2  \
          + (gamma*freq)**2))) + np.sqrt((epsilon_inf + w_p**2 * ((w_0**2 - freq**2)/((w_0**2 - freq**2)**2        \
          + (gamma*freq)**2)))**2 + ((w_p**2 * gamma * freq)/((w_0**2 - freq**2)**2 + (gamma*freq)**2))**2)))**2)
     
###################################################################################################################

wavenumbers, reflectance = data_import("MgO_data.csv",',')
wavenumbers2, n_lit = data_import("n_data.csv",',')
wavenumbers3, k_lit = data_import("k_data.csv",',')
wavenumbers4, eps1_lit = data_import("1_data.csv",',')
wavenumbers5, eps2_lit = data_import("2_data.csv",',')

reflect = reflectance / 100

c = 3e10
freq = 2*np.pi * c * wavenumbers

initial_guess = np.array([2.8650185, 1.92872821e14, 7.35717312e13, 3.81073635e12])

params, cov = curve_fit(Reflectance, freq, reflect, p0=initial_guess) 

epsilon_1, epsilon_2 = epsilon(freq, *params)
n = n_function(epsilon_1, epsilon_2)
k = k_function(epsilon_1, epsilon_2)


plt.figure("Reflectivity Data")
plt.plot(wavenumbers, reflectance, 'o', mfc='none', color='#1f77b4')
plt.plot(wavenumbers, Reflectance(freq, *params)*100, color='#1f77b4')

plt.xlabel("Wavenumber ($cm^{-1}$)")
plt.ylabel("Reflectance (%)")
plt.xlim(200,1200)
plt.ylim(0,100)


plt.figure("n and k Data")

plt.plot(wavenumbers2, n_lit, 'o', mfc='none', color='#1f77b4')
plt.plot(wavenumbers3, k_lit, 'o', mfc='none', color='#ff7f0e')
plt.plot(wavenumbers, n, color='#1f77b4', label='n')
plt.plot(wavenumbers, k, color='#ff7f0e', label='k')

plt.xlabel("Wavenumber ($cm^{-1}$)")
plt.ylabel("Optical Constants")
plt.xlim(200,1200)
plt.ylim(0,10)

plt.legend()


plt.figure("Epsilon_1 and Epsilon_2 data")
plt.plot(wavenumbers4, eps1_lit, 'o', mfc='none', color='#1f77b4')
plt.plot(wavenumbers5, eps2_lit, 'o', mfc='none', color='#ff7f0e')
plt.plot(wavenumbers, epsilon_1, label='$\\epsilon_1$', color='#1f77b4')
plt.plot(wavenumbers, epsilon_2, label='$\\epsilon_2$', color='#ff7f0e')

plt.xlabel("Wavenumber ($cm^{-1}$)")
plt.ylabel("Dielectric Functions")
plt.xlim(200,1200)
plt.ylim(-30,60)

plt.legend()
