#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Tue Mar  5 12:00:25 2019

Author: crdrisko

Description: Using the Hilbert transformation of ln(sqrt(R)) and phi, the absorption 
    index (k) can be produced from pure reflectance measurements.
"""

import numpy as np
import matplotlib.pyplot as plt
import scipy.fftpack as ft

reflect_data = np.loadtxt("Reflect_fig3.csv", delimiter = ",")
k_data = np.loadtxt("k_data_fig3.csv", delimiter = ",")

N_R = np.size(reflect_data)
wavenumbers_R = reflect_data[0:N_R:1,0]
Reflectance = reflect_data[0:N_R:1,1]

N_k = np.size(k_data)
wavenumbers_k = k_data[0:N_k:1,0]
k_lit = k_data[0:N_k:1,1] 

R = np.log(np.sqrt(Reflectance/100))

### Hilbert ###

phi_h = ft.hilbert(R)

k_hil = (2*np.sqrt(Reflectance/100)*np.sin(phi_h)) / (1 + (Reflectance/100) - 2*np.sqrt(Reflectance/100)*np.cos(phi_h))

plt.plot(wavenumbers_R, 3*k_hil+.2, 'r', label="k Hilbert")
plt.plot(wavenumbers_k, k_lit, 'k', label="k literature")

plt.xlabel("Wavenumbers ($cm^{-1}$)")
plt.ylabel("k")
plt.legend()

ax1 = plt.gca()
ax1.invert_xaxis()