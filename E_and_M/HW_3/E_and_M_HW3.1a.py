#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Tue Feb 12 09:30:29 2019

Author: crdrisko

Description: Epsilon 1 and 2 values for the following, insulators: BK7 and ITO; semi-conductors: 
    GaAs and CdTe; and metals: Au and Cu. n and k values were extracted from provided plots and 
    manually cut to equivalently sized arrays.
"""

import numpy as np
import matplotlib.pyplot as plt

#%% BK7 Glass

k_data_BK7 = np.loadtxt("k_data_BK7.dat", delimiter=" ")         
n_data_BK7 = np.loadtxt("n_data_BK7.dat", delimiter=" ")      

Nk_BK7 = np.size(k_data_BK7)
wavelength_k_BK7 = k_data_BK7[0:Nk_BK7:1, 0]
k_values_BK7 = k_data_BK7[0:Nk_BK7:1, 1]

Nn_BK7 = np.size(n_data_BK7)
wavelength_n_BK7 = n_data_BK7[0:Nn_BK7:1, 0]
n_values_BK7 = n_data_BK7[0:Nn_BK7:1, 1]

#plt.plot(wavelength_n_BK7, n_values_BK7, 'r', wavelength_k_BK7, k_values_BK7,'b')
    ## Values plot the correct graph ##
    
epsilon_1_BK7 = n_values_BK7**2 - k_values_BK7**2
epsilon_2_BK7 = 2 * n_values_BK7 * k_values_BK7

plt.plot(wavelength_k_BK7, epsilon_1_BK7, 'r', label='$\\epsilon_1$')
plt.plot(wavelength_k_BK7, epsilon_2_BK7, lineStyle='--', color='b', label='$\\epsilon_2$')

plt.legend()
plt.xlabel('Wavelength (nm)')
plt.ylabel('$\\epsilon_1$ and $\\epsilon_2$')
plt.title('Frequency-dependent $\\epsilon_1$ and $\\epsilon_2$ values for BK7 Glass')

#%% ITO

k_data_ITO = np.loadtxt("k_data_ITO.dat", delimiter=" ")         
n_data_ITO = np.loadtxt("n_data_ITO.dat", delimiter=" ")      

Nk_ITO = np.size(k_data_ITO)
wavelength_k_ITO = k_data_ITO[0:Nk_ITO:1, 0]
k_values_ITO = k_data_ITO[0:Nk_ITO:1, 1]

Nn_ITO = np.size(n_data_ITO)
wavelength_n_ITO = n_data_ITO[0:Nn_ITO:1, 0]
n_values_ITO = n_data_ITO[0:Nn_ITO:1, 1]

#plt.plot(wavelength_n_ITO, n_values_ITO, 'r', wavelength_k_ITO, k_values_ITO, 'b')
    ## Values plot the correct graph ##
    
epsilon_1_ITO = n_values_ITO**2 - k_values_ITO**2
epsilon_2_ITO = 2 * n_values_ITO * k_values_ITO

plt.plot(wavelength_k_ITO, epsilon_1_ITO, 'r', label='$\\epsilon_1$')
plt.plot(wavelength_k_ITO, epsilon_2_ITO, lineStyle='--', color='b', label='$\\epsilon_2$')

plt.legend()
plt.xlabel('Wavelength (nm)')
plt.ylabel('$\\epsilon_1$ and $\\epsilon_2$')
plt.title('Frequency-dependent $\\epsilon_1$ and $\\epsilon_2$ values for ITO')

#%% GaAs

k_data_GaAs = np.loadtxt("k_data_GaAs.dat", delimiter=" ")         
n_data_GaAs = np.loadtxt("n_data_GaAs.dat", delimiter=" ")      

Nk_GaAs = np.size(k_data_GaAs)
wavelength_k_GaAs = k_data_GaAs[0:Nk_GaAs:1, 0]
k_values_GaAs = k_data_GaAs[0:Nk_GaAs:1, 1]

Nn_GaAs = np.size(n_data_GaAs)
wavelength_n_GaAs = n_data_GaAs[0:Nn_GaAs:1, 0]
n_values_GaAs = n_data_GaAs[0:Nn_GaAs:1, 1]

#plt.plot(wavelength_n_GaAs, n_values_GaAs, 'r', wavelength_k_GaAs, k_values_GaAs, 'b')
    ## Values plot the correct graph ##
    
epsilon_1_GaAs = n_values_GaAs**2 - k_values_GaAs**2
epsilon_2_GaAs = 2 * n_values_GaAs * k_values_GaAs

plt.plot(wavelength_k_GaAs, epsilon_1_GaAs, 'r', label='$\\epsilon_1$')
plt.plot(wavelength_k_GaAs, epsilon_2_GaAs, lineStyle='--', color='b', label='$\\epsilon_2$')

plt.legend()
plt.xlabel('Wavelength (nm)')
plt.ylabel('$\\epsilon_1$ and $\\epsilon_2$')
plt.title('Frequency-dependent $\\epsilon_1$ and $\\epsilon_2$ values for GaAs')

#%% CdTe

k_data_CdTe = np.loadtxt("k_data_CdTe.dat", delimiter=" ")         
n_data_CdTe = np.loadtxt("n_data_CdTe.dat", delimiter=" ")      

Nk_CdTe = np.size(k_data_CdTe)
wavelength_k_CdTe = k_data_CdTe[0:Nk_CdTe:1, 0]
k_values_CdTe = k_data_CdTe[0:Nk_CdTe:1, 1]

Nn_CdTe = np.size(n_data_CdTe)
wavelength_n_CdTe = n_data_CdTe[0:Nn_CdTe:1, 0]
n_values_CdTe = n_data_CdTe[0:Nn_CdTe:1, 1]

#plt.plot(wavelength_n_CdTe, n_values_CdTe, 'r', wavelength_k_CdTe, k_values_CdTe, 'b')
    ## Values plot the correct graph ##
    
epsilon_1_CdTe = n_values_CdTe**2 - k_values_CdTe**2
epsilon_2_CdTe = 2 * n_values_CdTe * k_values_CdTe

plt.plot(wavelength_k_CdTe, epsilon_1_CdTe, 'r', label='$\\epsilon_1$')
plt.plot(wavelength_k_CdTe, epsilon_2_CdTe, lineStyle='--', color='b', label='$\\epsilon_2$')

plt.legend()
plt.xlabel('Wavelength (nm)')
plt.ylabel('$\\epsilon_1$ and $\\epsilon_2$')
plt.title('Frequency-dependent $\\epsilon_1$ and $\\epsilon_2$ values for CdTe')

#%% Au

k_data_Au = np.loadtxt("k_data_Au.dat", delimiter=" ")         
n_data_Au = np.loadtxt("n_data_Au.dat", delimiter=" ")      

Nk_Au = np.size(k_data_Au)
wavelength_k_Au = k_data_Au[0:Nk_Au:1, 0]
k_values_Au = k_data_Au[0:Nk_Au:1, 1]

Nn_Au = np.size(n_data_Au)
wavelength_n_Au = n_data_Au[0:Nn_Au:1, 0]
n_values_Au = n_data_Au[0:Nn_Au:1, 1]

#plt.plot(wavelength_n_Au, n_values_Au, 'r', wavelength_k_Au, k_values_Au, 'b')
    ## Values plot the correct graph ##
    
epsilon_1_Au = n_values_Au**2 - k_values_Au**2
epsilon_2_Au = 2 * n_values_Au * k_values_Au

plt.plot(wavelength_k_Au, epsilon_1_Au, 'r', label='$\\epsilon_1$')
plt.plot(wavelength_k_Au, epsilon_2_Au, lineStyle='--', color='b', label='$\\epsilon_2$')

plt.legend()
plt.xlabel('Wavelength (nm)')
plt.ylabel('$\\epsilon_1$ and $\\epsilon_2$')
plt.title('Frequency-dependent $\\epsilon_1$ and $\\epsilon_2$ values for Au')

#%% Cu

k_data_Cu = np.loadtxt("k_data_Cu.dat", delimiter=" ")         
n_data_Cu = np.loadtxt("n_data_Cu.dat", delimiter=" ")      

Nk_Cu = np.size(k_data_Cu)
wavelength_k_Cu = k_data_Cu[0:Nk_Cu:1, 0]
k_values_Cu = k_data_Cu[0:Nk_Cu:1, 1]

Nn_Cu = np.size(n_data_Cu)
wavelength_n_Cu = n_data_Cu[0:Nn_Cu:1, 0]
n_values_Cu = n_data_Cu[0:Nn_Cu:1, 1]

#plt.plot(wavelength_n_Cu, n_values_Cu, 'r', wavelength_k_Cu, k_values_Cu, 'b')
    ## Values plot the correct graph ##
    
epsilon_1_Cu = n_values_Cu**2 - k_values_Cu**2
epsilon_2_Cu = 2 * n_values_Cu * k_values_Cu

plt.plot(wavelength_k_Cu, epsilon_1_Cu, 'r', label='$\\epsilon_1$')
plt.plot(wavelength_k_Cu, epsilon_2_Cu, lineStyle='--', color='b', label='$\\epsilon_2$')

plt.legend()
plt.xlabel('Wavelength (nm)')
plt.ylabel('$\\epsilon_1$ and $\\epsilon_2$')
plt.title('Frequency-dependent $\\epsilon_1$ and $\\epsilon_2$ values for Cu')

