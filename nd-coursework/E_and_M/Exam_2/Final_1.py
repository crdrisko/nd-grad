#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Mon Apr 29 17:17:16 2019

Author: crdrisko

Description: An independent check on the data from the referecce below. Rather than use differential 
    reflectance spectroscopy, here we take the UV-vis absorbtion data and reproduce epsilon_1 
    and epsilon_2.
    
    References: "Optical Properties of Pyrolytic Carbon Films Versus Graphite and Graphene" 
                by Galyna I Dovbeshko, Volodymyr R Romanyuk, Denys V Pidgirnyi, Vsevolod V Cherepanov, 
                Eugene O Andreev, Vadim M Levin, Polina P Kuzhir, Tommi Kaplas and Yuri P Svirko
"""

import numpy as np
import matplotlib.pyplot as plt
import scipy.fftpack as ft
from Data_Import import data_import

wavelength, Absorption = data_import("Abs_data.csv", ',')
wavelength1, eps1_lit = data_import("eps1_data.csv", ',')
wavelength2, eps2_lit = data_import("eps2_data.csv", ',')


absorbance = np.zeros(71)
wavelength_360 = np.zeros(71)

for i in range (0, 71):
    absorbance[i] = Absorption[35 + i]
    wavelength_360[i] = wavelength[35 + i]

wavelength_padded = np.zeros(500)
wavelength_padded[0:71:1] = wavelength_360
wavelength_padded[71:500:1] = np.linspace(wavelength_360[70], 1100, 429)

abs_padded = np.zeros(500)
abs_padded[0:71:1] = absorbance
abs_padded[71:500:1] = absorbance[70]


plt.figure(1) 
plt.plot(wavelength_padded,abs_padded, color='#1f77b4', label="350-1100 nm range Absorbtion Spectra")
plt.plot(wavelength, Absorption, 'o', mfc='none', color='#1f77b4', label="UV-Vis Absorbtion Spectra")

plt.xlabel("Wavelength (nm)")
plt.ylabel("Absorption")
plt.xlim(150, 1100)
plt.ylim(0, 1.2) 

plt.legend()


c = 1e17                                        # nm/s
d = 5                                           # nm
n_inf = 1.43

alpha = abs_padded / d                          # nm^-1
freq = (2 * np.pi * c) / wavelength_padded
k = (alpha * c) / (2 * freq)
        
### Hilbert/Fourier Transform ###

n_hilbert = ft.hilbert(k)

epsilon_1 = n_hilbert**2 - k**2
epsilon_2 = 2 * n_hilbert * k

plt.figure(2)
plt.plot(wavelength_padded, -epsilon_1 + 2.5, color='#1f77b4', label="$\\epsilon_1$ Reproduced")
plt.plot(wavelength1, eps1_lit, 'o', mfc='none', color='#1f77b4', label="$\\epsilon_1$ Literature")
plt.plot(wavelength_padded, epsilon_2 + 6.4, color='#ff7f0e', label="$\\epsilon_2$ Reproduced")
plt.plot(wavelength2, eps2_lit, 'o', mfc='none', color='#ff7f0e', label="$\\epsilon_2$ Literature")
                
         
plt.xlabel("Wavelength (nm)")
plt.ylabel("Permitivity")
plt.xlim(350, 1120)
plt.ylim(0, 10)         
         
plt.legend()