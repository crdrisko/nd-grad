#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Thu Mar 21 13:09:50 2019

Author: crdrisko

Description: Drude oscillator analysis of reflectivity to reproduce experimental data    
    of IrO2 (Iridium oxide).
    
    Reference: "Investigation of the electrical and optical properties of iridium oxide 
        by reflectance FTIR spectroscopy and density functional theory calculations"
        by Scott H. Brewer, Dwi Wicaksana, Jon-Paul Maria, Angus I. Kingon, and Stefan Franzen
        
"""

import numpy as np
import matplotlib.pyplot as plt


Exp_data = np.loadtxt("Fig3_exp.csv", delimiter=",")
Calc_data = np.loadtxt("Fig3_calc.csv", delimiter=",")

N_exp = np.size(Exp_data)
wavenumbers_exp = Exp_data[0:N_exp:1, 0]                          # in 1e3 cm^-1
Reflect_exp = Exp_data[0:N_exp:1, 1]

N_calc = np.size(Calc_data)
wavenumbers_calc = Calc_data[0:N_calc:1, 0]                       # in 1e3 cm^-1
Reflect_calc = Calc_data[0:N_calc:1, 1]

wavenumbers_actual = wavenumbers_exp * 1e3

c = 1e10
theta_i = 60 * np.pi/180

##### Parameters #####
eps_inf = 6.4
w_p     = 20175 * 2 * np.pi * c
tau     = 8.55e-15
# By guess and check #

freq = (2 * np.pi * c * wavenumbers_actual)

epsilon_1 = eps_inf - (w_p**2 * tau**2)/(1 + (freq * tau)**2)
epsilon_2 = ((w_p**2 * tau)/freq) * (1/(1 + (freq * tau)**2))

n = 1/np.sqrt(2) * np.sqrt(epsilon_1 + np.sqrt(epsilon_1**2 + epsilon_2**2))
k = 1/np.sqrt(2) * np.sqrt(-epsilon_1 + np.sqrt(epsilon_1**2 + epsilon_2**2))

N = n + k*1j

r_p = (-N*np.cos(theta_i) + np.sqrt(1-(np.sin(theta_i)/N)**2)) / (N*np.cos(theta_i) \
        + np.sqrt(1-(np.sin(theta_i)/N)**2))

Reflect_Drude = r_p * np.conjugate(r_p) 


plt.plot(wavenumbers_exp, Reflect_exp, label='Experimental')
plt.plot(wavenumbers_calc, Reflect_calc, '--', label='Calculated (Literature)')
plt.plot(wavenumbers_exp, np.real(Reflect_Drude), label='Calculated (Drude)')


#plt.xlim(3,12.5)
#plt.ylim(0.0, 0.8)
plt.xlabel('Wavenumbers $(x10^3) (cm^{-1})$')
plt.ylabel('Reflectance')

plt.legend()