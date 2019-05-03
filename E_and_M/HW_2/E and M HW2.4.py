#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Mon Feb  4 10:03:44 2019

Author: crdrisko

Description: For an evanescent wave, a) the change in relative intensity vs. the 
penetration depth, and b) the penetration depth plotted against the incident angle.
"""

import numpy as np
import matplotlib.pyplot as plt

wavelength = 532                                                               # wavelength (nm)
n_i = 1.51                                                                     # refractive index first medium
n_t = 1.33                                                                     # refractive index second medium

theta_c = np.arcsin(n_t/n_i)                                                   # critical angle (radians)
theta_i = np.linspace(theta_c, np.pi/2,100)                                    # incident angle (radians) 

h_I = wavelength/(4*np.pi*np.sqrt(n_i**2*(np.sin(theta_i))**2-n_t**2))         # penetration depth (nm)

#%% Part a)

z = np.linspace(0,200,100)                                                     # distance z (nm)

Intensity_crit = np.exp(-z/h_I[0])
Intensity_mid = np.exp(-z/h_I[49])
Intensity_90 = np.exp(-z/h_I[99])

plt.plot(z,Intensity_crit, 'b', label="$\\theta_i = \\theta_c = 61.7^{\circ}$")
plt.plot(z,Intensity_mid, 'r', label="$\\theta_i = 75.7^{\circ}$")
plt.plot(z,Intensity_90, 'k', label="$\\theta_i = 90.0^{\circ}$")

plt.legend(loc= 'upper right', bbox_to_anchor=(1, .95))

plt.xlabel('Distance, z (nm)')
plt.ylabel('Intensity (nm)')
plt.title("Part a) Plot")


#%% Part b)

crit = np.array([theta_c, theta_c])
y = np.array([0,600])

plt.plot(theta_i*180/np.pi, h_I, 'b')
plt.plot(crit*180/np.pi, y, 'r', label="$\\theta_c = 61.738^{\circ}$")
plt.legend()

plt.xlabel('Angle of Incidence (Degrees)')
plt.ylabel('Penetration Depth (nm)')
plt.xlim(60, 90)
plt.ylim(0, 500)
plt.title("Part b) Plot")