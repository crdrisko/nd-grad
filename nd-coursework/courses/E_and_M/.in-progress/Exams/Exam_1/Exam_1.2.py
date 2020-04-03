#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Sat Mar  2 18:04:06 2019

Author: crdrisko

Description: A comparison of the Maclaurin approximation to both literature
    and the Hilbert/Fourier transform approach to the Kramers-Kronig formulas.
"""

import numpy as np
import matplotlib.pyplot as plt
import scipy.fftpack as ft

abs_data = np.loadtxt("Abs_fig2.csv", delimiter = ",")
n_data = np.loadtxt("n_data_fig2.csv", delimiter = ",")
k_data = np.loadtxt("k_data_fig2.csv", delimiter = ",")

N_abs = np.size(abs_data)
wavenumbers_abs = abs_data[0:N_abs:1,0]
absorbance = abs_data[0:N_abs:1,1]

N_n = np.size(n_data)
wavenumbers_n = n_data[0:N_n:1,0]
n_lit = n_data[0:N_n:1,1]

N_k = np.size(k_data)
wavenumbers_k = k_data[0:N_k:1,0]
k_lit = k_data[0:N_k:1,1] 

#plt.plot(wavenumbers_abs, absorbance, wavenumbers_n, n_lit, wavenumbers_k, k_lit)

c = 1e10                                    # cm/s
d = 0.000145                                # cm
n_inf = 1.43

alpha = absorbance/d                        # cm^-1
freq = (2 * np.pi * c * wavenumbers_abs)
k_reproduced = (alpha * c) / (2 * freq)

plt.figure("Figure 1")
plt.plot(wavenumbers_abs, k_reproduced, 'b', label="k reproduced")
plt.plot(wavenumbers_k, k_lit, 'r', label="k literature")

plt.xlabel("Wavenumbers ($cm^{-1}$)")
plt.ylabel("k")
plt.legend()

ax1 = plt.gca()
ax1.invert_xaxis()

### Maclaurin Approximation ###

n_Maclaurin = np.zeros(664)

for i in range(0,663):   
    f_j = 0
    if (i % 2):                             # i is odd
        for j in range(0,663,2):            # j is even
            f_j += ((k_reproduced[j] / (freq[j]-freq[i])) + (k_reproduced[j] / (freq[j]+freq[i])))
        n_Maclaurin[i] = (2/np.pi) * 2 * (freq[i+1] - freq[i]) * (1/2) * f_j
            
    else:                                   # i is even
        for j in range(1,663,2):            # j is odd            
            f_j += (k_reproduced[j] / (freq[j]-freq[i])) + (k_reproduced[j] / (freq[j]+freq[i]))
        n_Maclaurin[i] = (2/np.pi) * 2 * (freq[i+1] - freq[i]) * (1/2) * f_j                   
        
### Hilbert/Fourier Transform ###

n_hilbert = ft.hilbert(k_reproduced)

plt.figure("Figure 2")
plt.plot(wavenumbers_abs, -2*n_hilbert+1.4, 'r', label="n (Hilbert)")
plt.plot(wavenumbers_abs, -.5*n_Maclaurin+1.45, 'b', label="n (Maclaurin)")
plt.plot(wavenumbers_n, n_lit, 'k', label="n literature")

plt.xlabel("Wavenumbers ($cm^{-1}$)")
plt.ylabel("n")
plt.legend()

ax2 = plt.gca()
ax2.invert_xaxis()











