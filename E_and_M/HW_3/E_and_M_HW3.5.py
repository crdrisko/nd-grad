#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Wed Feb 13 09:58:56 2019

Author: crdrisko

Description: differences between n and k values from the literature 
    and the extracted alpha values. k values were padded and then the 
    Hilbert transformation was applied to produce the n values.
"""

import numpy as np
import matplotlib.pyplot as plt

### Literature Values ###

lit_values_k = np.loadtxt("lit_values_k_Si.dat", delimiter=" ")
lit_values_n = np.loadtxt("lit_values_n_Si.dat", delimiter=" ")

N_n = np.size(lit_values_n)
wavelength_n = lit_values_n[0:N_n:1, 0]
n_values_lit = lit_values_n[0:N_n:1, 1]

N_k = np.size(lit_values_k)
wavelength_k = lit_values_k[0:N_k:1, 0]
k_values_lit = lit_values_k[0:N_k:1, 1]

### From Alpha ###

alpha_data = np.loadtxt("alpha_data_Si.dat", delimiter=" ")

N_alpha = np.size(alpha_data)
wavelength_alpha = alpha_data[0:N_alpha:1, 0]
alpha_values = alpha_data[0:N_alpha:1, 1]

c = 3e17
freq = ((2 * np.pi * c)/wavelength_alpha)/1e16          # Frequency in 10^16 s^-1
k = (c * alpha_values/1e7) / (2 * freq*1e16)            # alpha_values: cm^-1 --> nm^-1

k_padded = np.zeros(1000)
k_padded[0:190:1]=-np.linspace(0,.006,190)
k_padded[190:298:1]=-np.flip(k,0)
k_padded[298:500:1]=-np.linspace(2.7,0,202)

k_padded[500:702:1]=np.linspace(0,2.7,202)
k_padded[702:810:1]=k
k_padded[810:1000:1]=np.linspace(.006,0,190)

wavelength_padded = np.zeros(1000)
wavelength_padded[0:190:1]=-np.linspace(1000,798,190)
wavelength_padded[190:298:1]=-np.flip(wavelength_alpha,0)
wavelength_padded[298:500:1]=-np.linspace(187,0,202) 

wavelength_padded[500:702:1]=np.linspace(0,187,202)
wavelength_padded[702:810:1]=wavelength_alpha
wavelength_padded[810:1000:1]= np.linspace(798,1000,190)

k_FT = np.fft.fft(k_padded, norm="ortho").imag
k_FT[0:int(len(k_FT)/2)]=0
n = np.fft.fft(k_FT, norm="ortho")

#plt.plot(wavelength_padded,k_padded)

plt.plot(wavelength_padded, -3 * n.real + 1 , 'm', label='n experimental values')
plt.plot(wavelength_n, n_values_lit, color='c', label='n literature values')

plt.plot(wavelength_alpha, k, color='r', label='k experimental values')
plt.plot(wavelength_k, k_values_lit, color='b', label='k literature values')

plt.legend()
plt.xlim(150,800)
plt.xlabel('Wavelength (nm)')
plt.ylabel('n and k')
