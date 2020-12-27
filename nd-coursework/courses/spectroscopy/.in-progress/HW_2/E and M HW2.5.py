#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Mon Feb  4 10:03:44 2019

Author: crdrisko

Description: Transmitance intesity and incidence intensity ratio for s- and p-polarization 
plotted against the angle of incidence.
"""

import numpy as np
import matplotlib.pyplot as plt

n_i = 1.51
n_t = 1.33
n = n_t/n_i

theta_c = np.arcsin(n_t/n_i)                                                   # critical angle (radians)
theta_i = np.linspace(theta_c, np.pi/2,100)                                    # incident angle (radians)

Int_ratio_s = (4*(np.cos(theta_i))**2)/(1-n**2)

Int_ratio_p = (4*(np.cos(theta_i))**2 * (2*((np.sin(theta_i))**2) - n**2)) \
    /(n**4 * (np.cos(theta_i))**2 + (np.sin(theta_i))**2 - n**2)

plt.plot(theta_i*180/np.pi, Int_ratio_s, 'b', label="s-polarization") 
plt.plot(theta_i*180/np.pi, Int_ratio_p, 'r', label="p-polarization")
plt.legend()

plt.xlabel('Angle of Incidence (Degrees)')
plt.ylabel('$I_t / I_i$')
