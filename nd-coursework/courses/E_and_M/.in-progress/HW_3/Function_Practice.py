#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Wed Jun 19 16:02:56 2019

Author: crdrisko

Description: An script that is a direct improvement over the E_and_M_HW3.1a and E_and_M_HW3.1b
    programs I had previously written. By implementing simple functions and combining the two scripts
    I was able to cut the code from two 100+ line programs to one 75 line program. 

    Epsilon 1 and 2 values and reflectance values for the following, insulators: BK7 and ITO; 
    semi-conductors: GaAs and CdTe; and metals: Au and Cu. n and k values were extracted from 
    provided plots and manually cut to equivalently sized arrays.
"""

import numpy as np
import matplotlib.pyplot as plt

### Functions ###

def dataImport(material, prop):
    fileName = str(prop) + "_data_" + str(material) + ".dat"
    data = np.loadtxt(fileName, delimiter=' ')
    N = np.size(data)
    
    return data[0:N:1, 0], data[0:N:1, 1]

def epsilonPlotter(material):
    wavelength_n, n_values = dataImport(material, 'n')
    wavelength_k, k_values = dataImport(material, 'k')
    
    epsilon_1 = n_values**2 - k_values**2
    epsilon_2 = 2 * n_values * k_values
    
    reflect = ((n_values - 1)**2 + k_values**2)/((n_values + 1)**2 + k_values**2)
    
    plt.figure()
    plt.plot(wavelength_n, n_values, color='r', label='n')
    plt.plot(wavelength_k, k_values, color='b', label='k')

    plt.xlabel("Wavelength ($\\mu m$)")
    plt.ylabel("n and k")
    plt.title("Frequency-dependent n and k values for %s" % str(material))
    plt.legend()
    
    plt.figure()
    plt.plot(wavelength_k, epsilon_1, 'r', label="$\\epsilon_1$")
    plt.plot(wavelength_k, epsilon_2, lineStyle="--", color='b', label="$\\epsilon_2$")
    
    plt.xlabel("Wavelength (nm)")
    plt.ylabel("$\\epsilon_1$ and $\\epsilon_2$")
    plt.title("Frequency-dependent $\\epsilon_1$ and $\\epsilon_2$ values for %s" % str(material))
    plt.legend()
    
    plt.figure()
    plt.plot(wavelength_k, reflect, 'r')

    plt.xlabel("Wavelength (nm)")
    plt.ylabel("Reflectance ($\\mathcal{R}$)")
    plt.title("Reflectance for %s" % str(material))
    
    return n_values, k_values, epsilon_1, epsilon_2, reflect


### Main Code ###
    
    ## Question 1 ##
n_values_BK7, k_values_BK7, epsilon_1_BK7, epsilon_2_BK7, reflect_BK7 = epsilonPlotter("BK7")
n_values_ITO, k_values_ITO, epsilon_1_ITO, epsilon_2_ITO, reflect_ITO = epsilonPlotter("ITO")
n_values_GaAs, k_values_GaAs, epsilon_1_GaAs, epsilon_2_GaAs, reflect_GaAs = epsilonPlotter("GaAs")
n_values_CdTe, k_values_CdTe, epsilon_1_CdTe, epsilon_2_CdTe, reflect_CdTe = epsilonPlotter("CdTe")
n_values_Au, k_values_Au, epsilon_1_Au, epsilon_2_Au, reflect_Au = epsilonPlotter("Au")
n_values_Cu, k_values_Cu, epsilon_1_Cu, epsilon_2_Cu, reflect_Cu = epsilonPlotter("Cu")
