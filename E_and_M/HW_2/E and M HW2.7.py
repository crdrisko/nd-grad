#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Sun Feb 10 14:55:59 2019

Author: crdrisko

Description: Code to reproduce the epsilon double prime figure from 
    the reflection figure in the journal article: T. Dienel, R. Forker, K. Leo, T. Fritz, 
    Optical differential reflectance spectroscopy of molecular thin films on a metal: 
    Evidence for strong oscillator strength increase, 
    J. Phys. Chem. C 2007, 111, 14593.
    
    Refractive index provided by: https://refractiveindex.info/?shelf=main&book=Au&page=Werner-DFT
"""

import numpy as np
import matplotlib.pyplot as plt

data_set = np.loadtxt("Data_fig2.dat", delimiter=" ")

N = np.size(data_set)
energy = data_set[0:N:1, 0]
deltaR_R = data_set[0:N:1, 1]

h = 6.626e-34                                   # planck's constant (J s)
c = 3e17                                        # speed of light (nm/s)
n_gold = 1.5128                                 # refractive index of gold at 532 nm
d = 5.5 * .33                                   # 5.5 ML's * .33 nm

eps2 = deltaR_R * ((h*c/(energy*1.60218e-19)) * (n_gold**2 - 1)/(8*np.pi*d))

fig, ax1 = plt.subplots()

ax2 = ax1.twiny()
ax1.plot(energy, eps2*1.4, 'k')

ax2.set_xticks([])

ax1.set_xlabel('E (eV)')
ax1.set_ylabel('$\\epsilon$\"')
ax2.set_xlabel('$\\lambda$ (nm)')

