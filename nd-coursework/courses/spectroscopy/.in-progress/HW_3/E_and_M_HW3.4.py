#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Thu Feb 14 10:48:36 2019

Author: crdrisko

Description: Comparison between the Lorenz Model, the Fourier Transform model,
    and the Hilbert Model for both epsilon 1 and 2.
"""

import numpy as np
import matplotlib.pyplot as plt
import scipy.fftpack as ft

### Exact ###

freq_0 = 4.0                                   # resonance frequency in arbitrary units
freq_p = 8.0                                   # bulk plasma frequency in arbitrary units
gamma = 1.0                                    # empirical damping parameter in arbitrary units

freq = np.linspace(-12,12, 241)

epsilon_1 = 1 + freq_p**2 * (freq_0**2 - freq**2)/((freq_0**2 - freq**2)**2 + (freq*gamma)**2)
epsilon_2 = freq_p**2 * (freq*gamma)/((freq_0**2 - freq**2)**2 + (freq*gamma)**2)


### Fourier ###

FT_epsilon_2 = np.fft.fft(epsilon_2, norm="ortho").imag
FT_epsilon_2[0:int(len(FT_epsilon_2)/2)]=0

FT_FT_epsilon_1 = np.fft.fft(FT_epsilon_2, norm="ortho")

FT_epsilon_1 = np.fft.fft(epsilon_1, norm="ortho").real
FT_epsilon_1[0:int(len(FT_epsilon_1)/2)]=0

FT_FT_epsilon_2 = np.fft.fft(FT_epsilon_1, norm="ortho")


### Hilbert ###

eps1_hilb = ft.hilbert(epsilon_2) + 1
eps2_hilb = ft.hilbert(-epsilon_1 + 1)


### Epsilon 1 and 2 Plots ###

plt.figure('1')
plt.plot(freq, epsilon_1, lineStyle='--', color='r', label='$\\epsilon_1$ Lorentz')
plt.plot(freq, 2*FT_FT_epsilon_1.real + 1, label ='$\\epsilon_1$ Fourier')
plt.plot(freq, eps1_hilb, ':m', label='$\\epsilon_1$ Hilbert')

plt.xlabel('$\\omega (arb)$')
plt.ylabel('$\\epsilon_1(\\omega)$')
plt.xlim(0, 12)
plt.legend()


plt.figure('2')
plt.plot(freq, epsilon_2, lineStyle='--', color='r', label='$\\epsilon_2$ Lorentz')
plt.plot(freq, 2*FT_FT_epsilon_2.imag, label ='$\\epsilon_2$ Fourier')
plt.plot(freq, eps2_hilb, ':m', label='$\\epsilon_2$ Hilbert')

plt.xlabel('$\\omega (arb)$')
plt.ylabel('$\\epsilon_2(\\omega)$')
plt.xlim(0, 12)
plt.ylim(0,17)
plt.legend()
