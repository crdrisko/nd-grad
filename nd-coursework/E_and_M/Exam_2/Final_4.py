#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Mon Apr 29 09:37:24 2019

Author: crdrisko

Description: Mie Theory code for the calculation of C_extinction and C_scattering.

     References: 1) "Optical extinction spectroscopy of single silver nanoparticles" by P. Billaud, 
                    J.-R. Huntzinger, E. Cottancin, J. Lerme, M. Pellarin, L. Arnaud, M. Broyer,
                    N. Del Fatti, and F. Vallee
                 2) "Optical Constants of the Noble Metals" by P. B. Johnson and R. W. Christy 
                 3) "Field Enhancement around Metal Nanoparticles and Nanoshells: A Systematic 
                    Investigation" by Katsuaki Tanabe
          
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.special import spherical_jn, spherical_yn
from Data_Import import data_import

###########################################          Functions          #############################

def spherical_hn(n,z):               # Spherical Hankel Function of the first kind
    return spherical_jn(n,z) + 1j * spherical_yn(n,z)
                                                                                                        
def d_spherical_hn(n,z):             # Derivative of the Spherical Hankel Function of the first kind
    return 1/2 * (spherical_hn(n-1,z) - (spherical_hn(n,z) + z * (spherical_hn(n+1,z)))/z)

def eps_fcn(lambda_fcn,a6,a5,a4,a3,a2,a1,a0):
    return a6*lambda_fcn**6 + a5*lambda_fcn**5 + a4*lambda_fcn**4 + a3*lambda_fcn**3 + \
        a2*lambda_fcn**2 + a1*lambda_fcn + a0  
        
def lambda_max_finder(C_ext,wavelength):
    for i in range(0,1800):
        if (np.amax(np.real(C_ext)) == C_ext[i]):
            return wavelength[i]        

#####################################################################################################
            
### Data from Johnson & Christy ###

x_vals, y_vals = data_import("Lit_ext.csv",',')
optical_data = np.loadtxt("n_k_data.csv", delimiter=', ', skiprows=1)

N = np.size(optical_data)
eV = optical_data[0:N:1, 0]                             # Photon Energy (eV)
n_metal = optical_data[0:N:1, 1]
k_metal = optical_data[0:N:1, 2]

planck = 4.135667662e-15                                # Planck's Constant (eV s)
c = 3e17                                                # Speed of light (nm/s)
wavelength = (planck * c) / np.flip(eV,0)               # wavelength (nm)

n_med = 1.47
a = 31 / 2                                              # Radius of nanoparticle (nm)

eps1 = n_metal**2 - k_metal**2
eps2 = 2 * n_metal * k_metal

m = (np.flip(n_metal,0) + 1j*np.flip(k_metal,0))/n_med
x = (2 * np.pi * n_med * a) / wavelength
mx = m * x

a_l = np.zeros(10, dtype=complex)
b_l = np.zeros(10, dtype=complex)
C_ext = np.zeros(49, dtype=complex)
C_scat = np.zeros(49, dtype=complex)

for i in range(0,49):
    for l in range(1, 11):
        a_l[l-1] = (m[i]**2 * spherical_jn(l, mx[i]) * (spherical_jn(l, x[i]) + x[i]                \
                 * spherical_jn(l, x[i], derivative=True)) - spherical_jn(l, x[i])                  \
                 * (spherical_jn(l, mx[i]) + mx[i] * spherical_jn(l, mx[i], derivative=True)))      \
                 / (m[i]**2 * spherical_jn(l, mx[i]) * (spherical_hn(l,x[i]) + x[i]                 \
                 * d_spherical_hn(l, x[i])) - spherical_hn(l, x[i]) * ( spherical_jn(l, mx[i])      \
                 + mx[i] * spherical_jn(l, mx[i], derivative=True)))
       
        b_l[l-1] = (spherical_jn(l, mx[i]) * (spherical_jn(l, x[i]) + x[i]                          \
                 * spherical_jn(l, x[i], derivative=True)) - spherical_jn(l, x[i])                  \
                 * (spherical_jn(l, mx[i]) + mx[i] * spherical_jn(l, mx[i], derivative=True)))      \
                 / (spherical_jn(l, mx[i]) * (spherical_hn(l, x[i]) + x[i]                          \
                 * d_spherical_hn(l, x[i])) - spherical_hn(l, x[i]) * ( spherical_jn(l, mx[i])      \
                 + mx[i] * spherical_jn(l, mx[i], derivative=True)))
                 
        C_scat[i] += (wavelength[i]**2 / (2*np.pi * n_med**2)) * ((2*l + 1) * (a_l[l-1]             \
                   * np.conjugate(a_l[l-1]) + b_l[l-1] * np.conjugate(b_l[l-1])))
               
        C_ext[i]  += (wavelength[i]**2 / (2*np.pi*n_med**2)) * ((2*l + 1) * np.real(a_l[l-1]        \
                   + b_l[l-1]))
        

### Data from Tanabe ###

     ## Wavelengths ##
lambda_short1 = np.linspace(200,310,111)
lambda_long1  = np.linspace(311,2000,1690)
lambda_short2 = np.linspace(200,330,131)
lambda_long2  = np.linspace(331,2000,1670)
     
     ## Parameters ##
          # Epsilon 1 @ small wavelengths #
a6,a5,a4,a3,a2,a1,a0 = -1.308415e-11,1.764343e-8,-9.761668e-6,2.832725e-3,-.4538023,37.94213,-1.288348e3
          # Epsilon 1 @ long wavelengths # 
b6,b5,b4,b3,b2,b1,b0 = -2.037181e-17,1.183540e-13,-2.537882e-10,2.430043e-7,-1.420089e-4,8.990214e-4,\
                        8.526028
          # Epsilon 2 @ small wavelengths #
c6,c5,c4,c3,c2,c1,c0 =  3.636188e-11,-5.443344e-8,3.365273e-5,-1.100094e-2,2.005786,-193.4021,7.706263e3
          # Epsilon 2 @ long wavelengths #
d6,d5,d4,d3,d2,d1,d0 = -2.327098e-17,1.471828e-13,-3.635520e-10,4.530857e-7,-2.946733e-4,9.562290e-2,\
                        -11.49465

eps_1_sw = eps_fcn(lambda_short1,a6,a5,a4,a3,a2,a1,a0)
eps_1_lw = eps_fcn(lambda_long1,b6,b5,b4,b3,b2,b1,b0)    
eps_2_sw = eps_fcn(lambda_short2,c6,c5,c4,c3,c2,c1,c0)
eps_2_lw = eps_fcn(lambda_long2,d6,d5,d4,d3,d2,d1,d0)

    ## Adjustments ##
eps_1_tot = np.zeros(1801)
eps_1_tot[0:111:1] = eps_1_sw
eps_1_tot[111:1801:1] = eps_1_lw

eps_2_tot = np.zeros(1801)
eps_2_tot[0:131:1] = eps_2_sw
eps_2_tot[131:1801:1] = eps_2_lw

wavelength1 = np.zeros(1801)
wavelength1[0:111:1] = lambda_short1
wavelength1[111:1801:1] = lambda_long1


n_metal1 = 1/np.sqrt(2) * np.sqrt(eps_1_tot + np.sqrt(eps_1_tot**2 + eps_2_tot**2))
k_metal1 = 1/np.sqrt(2) * np.sqrt(-eps_1_tot + np.sqrt(eps_1_tot**2 + eps_2_tot**2))


m1 = (n_metal1 + 1j*k_metal1)/n_med
x1 = (2 * np.pi * n_med * a) / wavelength1
mx1 = m1 * x1

a1_l = np.zeros(10, dtype=complex)
b1_l = np.zeros(10, dtype=complex)
C_ext1 = np.zeros(1801, dtype=complex)
C_scat1 = np.zeros(1801, dtype=complex)

for i in range(0,1801):
    for l in range(1, 11):
        a1_l[l-1] = (m1[i]**2 * spherical_jn(l, mx1[i]) * (spherical_jn(l, x1[i]) + x1[i]           \
                 * spherical_jn(l, x1[i], derivative=True)) - spherical_jn(l, x1[i])                \
                 * (spherical_jn(l, mx1[i]) + mx1[i] * spherical_jn(l, mx1[i], derivative=True)))   \
                 / (m1[i]**2 * spherical_jn(l, mx1[i]) * (spherical_hn(l,x1[i]) + x1[i]             \
                 * d_spherical_hn(l, x1[i])) - spherical_hn(l, x1[i]) * ( spherical_jn(l, mx1[i])   \
                 + mx1[i] * spherical_jn(l, mx1[i], derivative=True)))
       
        b1_l[l-1] = (spherical_jn(l, mx1[i]) * (spherical_jn(l, x1[i]) + x1[i]                      \
                 * spherical_jn(l, x1[i], derivative=True)) - spherical_jn(l, x1[i])                \
                 * (spherical_jn(l, mx1[i]) + mx1[i] * spherical_jn(l, mx1[i], derivative=True)))   \
                 / (spherical_jn(l, mx1[i]) * (spherical_hn(l, x1[i]) + x1[i]                       \
                 * d_spherical_hn(l, x1[i])) - spherical_hn(l, x1[i]) * ( spherical_jn(l, mx1[i])   \
                 + mx1[i] * spherical_jn(l, mx1[i], derivative=True)))
                 
        C_scat1[i] += (wavelength1[i]**2 / (2*np.pi * n_med**2)) * ((2*l + 1) * (a1_l[l-1]          \
                    * np.conjugate(a1_l[l-1]) + b1_l[l-1] * np.conjugate(b1_l[l-1])))
               
        C_ext1[i]  += (wavelength1[i]**2 / (2*np.pi*n_med**2)) * ((2*l + 1) * np.real(a1_l[l-1]     \
                    + b1_l[l-1]))


### Adjustments to the data to overlay the graphs for comparison ###
        
lambda_max_lit = lambda_max_finder(y_vals,x_vals)
lambda_max = lambda_max_finder(C_ext,wavelength)
lambda_max1 = lambda_max_finder(C_ext1, wavelength1)

alpha = np.max(y_vals) / np.max(np.real(C_ext))
alpha1 = np.max(y_vals)/np.max(np.real(C_ext1))

beta = np.real(lambda_max) - lambda_max_lit
beta1 = np.real(lambda_max1) - lambda_max_lit


### Plots of Dielectric Functions and Extinction Cross Sections ###

plt.figure(1)
plt.plot(eV, eps1, label='$\\epsilon_1$')
plt.plot(eV, eps2, label='$\\epsilon_2$')

plt.xlabel("Photon Energy (eV)")
plt.xlim(0,7)
plt.ylim(-7,7)

plt.legend()


plt.figure(2)
plt.plot(x_vals, y_vals, label='Literature Mie Theory')
plt.plot(wavelength, np.real(C_ext)*alpha, label='Mie Theory Code')

plt.xlabel('Wavelength (nm)')
plt.ylabel('$\\sigma_{ext}$ ($nm^2$)')
plt.xlim(350,550)
plt.ylim(0,1.2e4)   

plt.legend()  


plt.figure(3)
plt.plot(x_vals, y_vals, label='Literature Mie Theory')
plt.plot(wavelength - beta, np.real(C_ext)*alpha, label='Johnson & Christy Data')
plt.plot(wavelength1 - beta1, np.real(C_ext1)*alpha1, label='Tanabe Data')

plt.xlabel('Wavelength (nm)')
plt.ylabel('$\\sigma_{ext}$ ($nm^2$)')
plt.xlim(350,550)
plt.ylim(0,1.2e4)   

plt.legend()  