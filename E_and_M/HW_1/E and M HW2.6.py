#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Sun Feb 10 11:08:39 2019

Author: crdrisko

Description: Code to reproduce the absorbance figure from the reflection figure in the journal article:
    K. F. Mak, C. Lee J. Hone, J. Shan, T. F. Heinz, Atomically thin MoS2: A new direct-gap semiconductor, 
    Phys. Rev. Lett. 2010, 136805
    
    Refractive index provided by: https://refractiveindex.info/?shelf=glass&book=fused_silica&page=Malitson
    
"""

import numpy as np
import matplotlib.pyplot as plt

data_set1a = np.loadtxt("Data_1lay.dat", delimiter=" ")         # 1 layer, N=1, reflection data
data_set1b = np.loadtxt("Data2_1lay.dat", delimiter=" ")        # 1 layer, Normalized PL data

### Relative Reflectance Data for 1 layer ###
N1a = np.size(data_set1a)
photon_energy1 = data_set1a[0:N1a:1, 0]
delta_1 = data_set1a[0:N1a:1, 1]

### Photoluminescence Data for 1 layer ###
N1b = np.size(data_set1b)
photon_energy1b = data_set1b[0:N1b:1, 0]
PL_norm1 = data_set1b[0:N1b:1, 1]


data_set2a = np.loadtxt("Data_2lay.dat", delimiter=" ")         # 2 layers, N=2, reflection data
data_set2b = np.loadtxt("Data2_2lay.dat", delimiter=" ")        # 2 layers, Normalized PL data

### Relative Reflectance Data for 2 layers ###
N2a = np.size(data_set2a)
photon_energy2 = data_set2a[0:N2a:1, 0]
delta_2 = data_set2a[0:N2a:1, 1]

### Photoluminescence Data for 2 layers ###
N2b = np.size(data_set2b)
photon_energy2b = data_set2b[0:N2b:1, 0]
PL_norm2 = data_set2b[0:N2b:1, 1]

n_sub = 1.4607                                                  # refractive index of fused silica @ 532 nm

abs1 = ((n_sub**2 - 1)/4)*(delta_1/100)
abs2 = ((n_sub**2 - 1)/4)*(delta_2/100)


fig, ax1 = plt.subplots()

ax2 = ax1.twinx()
ax1.plot(photon_energy1, abs1, 'k')
ax1.plot(photon_energy2, abs2/2 + .1, 'k')
ax1.plot(photon_energy1b, (PL_norm1/100)/.1, 'r')
ax1.plot(photon_energy2b, (PL_norm2/100)/.0925, 'r')


ax1.set_xlabel('Photon Energy (eV)')
ax1.set_ylabel('Absorbance/Layer')
ax2.set_ylabel('Normalized PL (a.u.)')

ax1.set_xlim(1.3, 2.4)
ax1.set_ylim(-.025, .3)
ax2.set_ylim(-.025, .3)

ax1.annotate('A', xy=(1.85, .225), xycoords= 'data')
ax1.annotate('B', xy=(2.0, .22), xycoords= 'data')
ax1.annotate('1', color='b', xy=(1.45, .225), xycoords= 'data')
ax1.annotate('2lay', xy=(2.25, .175), xycoords= 'data')
ax1.annotate('1lay', xy=(2.25, .055), xycoords= 'data')
ax1.annotate('Laser Excitation', color='g', xy=(2.0, .255), xycoords= 'data')
ax1.annotate('(a)', xy=(1.325, .275), xycoords= 'data')

