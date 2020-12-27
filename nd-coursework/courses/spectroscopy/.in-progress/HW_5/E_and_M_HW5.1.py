 #!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Mon Apr  8 15:27:35 2019

Author: crdrisko

Description: Reproducing the silver plot from the fit functions provided in the literature.
    Ref: "Field Enhancement around Metal Nanoparticles and Nanoshells: A Systematic Investigation"
        by Katsuaki Tanabe
"""

import numpy as np
import matplotlib.pyplot as plt

a0_data = np.loadtxt("a_0.csv", delimiter=",")         
a2_data = np.loadtxt("ar_2.csv", delimiter=",")   
a4_data = np.loadtxt("ar_4.csv", delimiter=",")   
a6_data = np.loadtxt("ar_6.csv", delimiter=",")  
a8_data = np.loadtxt("ar_8.csv", delimiter=",")   
a1_data = np.loadtxt("ar_1.csv", delimiter=",")    

N_a0 = np.size(a0_data)
wavelength_a0 = a0_data[0:N_a0:1, 0]                             # in nanometers
field_factor_a0 = a0_data[0:N_a0:1, 1]

N_a2 = np.size(a2_data)
wavelength_a2 = a2_data[0:N_a2:1, 0]                             # in nanometers
field_factor_a2 = a2_data[0:N_a2:1, 1]

N_a4 = np.size(a4_data)
wavelength_a4 = a4_data[0:N_a4:1, 0]                             # in nanometers
field_factor_a4 = a4_data[0:N_a4:1, 1]

N_a6 = np.size(a6_data)
wavelength_a6 = a6_data[0:N_a6:1, 0]                             # in nanometers
field_factor_a6 = a6_data[0:N_a6:1, 1]

N_a8 = np.size(a8_data)
wavelength_a8 = a8_data[0:N_a8:1, 0]                             # in nanometers
field_factor_a8 = a8_data[0:N_a8:1, 1]

N_a1 = np.size(a1_data)
wavelength_a1 = a1_data[0:N_a1:1, 0]                             # in nanometers
field_factor_a1 = a1_data[0:N_a1:1, 1]

### Fit Function from Literature ###

     ## Wavelengths ##
lambda_short1 = np.linspace(200,310,111)
lambda_long1  = np.linspace(311,2000,1690)
lambda_short2 = np.linspace(200,330,131)
lambda_long2  = np.linspace(331,2000,1670)
     
     ## Parameters ##
          # Epsilon 1 @ small wavelengths #
a6 = -1.308415e-11
a5 =  1.764343e-8
a4 = -9.761668e-6
a3 =  2.832725e-3
a2 = -4.538023e-1
a1 =  3.794213e1
a0 = -1.288348e3
          # Epsilon 1 @ long wavelengths # 
b6 = -2.037181e-17
b5 =  1.183540e-13
b4 = -2.537882e-10
b3 =  2.430043e-7 
b2 = -1.420089e-4 
b1 =  8.990214e-4
b0 =  8.526028e0
          # Epsilon 2 @ small wavelengths #
c6 =  3.636188e-11
c5 = -5.443344e-8
c4 =  3.365273e-5
c3 = -1.100094e-2
c2 =  2.005786e0
c1 = -1.934021e2
c0 =  7.706263e3
          # Epsilon 2 @ long wavelengths #
d6 = -2.327098e-17 
d5 =  1.471828e-13
d4 = -3.635520e-10
d3 =  4.530857e-7
d2 = -2.946733e-4
d1 =  9.562290e-2
d0 = -1.149465e1

     ## Functions ##
eps_1_sw = a6*lambda_short1**6 + a5*lambda_short1**5 + a4*lambda_short1**4 + a3*lambda_short1**3 + \
    a2*lambda_short1**2 + a1*lambda_short1 + a0

eps_1_lw = b6*lambda_long1**6 + b5*lambda_long1**5 + b4*lambda_long1**4 + b3*lambda_long1**3 + \
    b2*lambda_long1**2 + b1*lambda_long1 + b0

eps_2_sw = c6*lambda_short2**6 + c5*lambda_short2**5 + c4*lambda_short2**4 + c3*lambda_short2**3 + \
    c2*lambda_short2**2 + c1*lambda_short2 + c0
     
eps_2_lw = d6*lambda_long2**6 + d5*lambda_long2**5 + d4*lambda_long2**4 + d3*lambda_long2**3 + \
    d2*lambda_long2**2 + d1*lambda_long2 + d0    

    ## Adjustments ##
eps_1_tot = np.zeros(1801)
eps_1_tot[0:111:1] = eps_1_sw
eps_1_tot[111:1801:1] = eps_1_lw


eps_2_tot = np.zeros(1801)
eps_2_tot[0:131:1] = eps_2_sw
eps_2_tot[131:1801:1] = eps_2_lw

wavelength = np.zeros(1801)
wavelength[0:111:1] = lambda_short1
wavelength[111:1801:1] = lambda_long1


#plt.figure("Figure 1")
#plt.plot(wavelength,eps_1_tot,'r',label="$\\epsilon_1$")
#plt.plot(wavelength,eps_2_tot,'b',label="$\\epsilon_2$")
#
#plt.xlabel('Wavelength in vacuo (nm)')
#plt.ylabel('Real and imaginary parts of dielectric fuction $\\epsilon_1$(-) and $\\epsilon_2$(-)')
#plt.xlim(0,1000)
#plt.ylim(-50,10)
#
#plt.legend()

epsilon_1 = eps_1_tot + 1j*eps_2_tot
epsilon_m = 1

radius_ratio1 = 0
radius_ratio2 = 0.2
radius_ratio3 = 0.4
radius_ratio4 = 0.6
radius_ratio5 = 0.8
radius_ratio6 = 1

beta = (epsilon_1 - epsilon_m) / (epsilon_1 + 2*epsilon_m)

field_factor1 = (1 + 2 * (radius_ratio1)**3 * beta) * np.conjugate(1 + 2 * (radius_ratio1)**3 * beta)  
field_factor2 = (1 + 2 * (radius_ratio2)**3 * beta) * np.conjugate(1 + 2 * (radius_ratio2)**3 * beta)      
field_factor3 = (1 + 2 * (radius_ratio3)**3 * beta) * np.conjugate(1 + 2 * (radius_ratio3)**3 * beta)     
field_factor4 = (1 + 2 * (radius_ratio4)**3 * beta) * np.conjugate(1 + 2 * (radius_ratio4)**3 * beta)      
field_factor5 = (1 + 2 * (radius_ratio5)**3 * beta) * np.conjugate(1 + 2 * (radius_ratio5)**3 * beta)      
field_factor6 = (1 + 2 * (radius_ratio6)**3 * beta) * np.conjugate(1 + 2 * (radius_ratio6)**3 * beta)      

orange = '#FFA500'
purple = '#800080'

#plt.figure("Figure 2")
plt.plot(wavelength, np.real(field_factor1), 'r', label="a/r=0")
plt.plot(wavelength, np.real(field_factor2), orange, label="a/r=0.2")
plt.plot(wavelength, np.real(field_factor3), 'g', label="a/r=0.4")
plt.plot(wavelength, np.real(field_factor4), 'b', label="a/r=0.6")
plt.plot(wavelength, np.real(field_factor5), purple, label="a/r=0.8")
plt.plot(wavelength, np.real(field_factor6), 'k', label="a/r=1")
plt.plot(wavelength_a0, field_factor_a0, ".", color = 'r')
plt.plot(wavelength_a2, field_factor_a2, ".", color = orange)
plt.plot(wavelength_a4, field_factor_a4, ".", color = 'g')
plt.plot(wavelength_a6, field_factor_a6, ".", color = 'b')
plt.plot(wavelength_a8, field_factor_a8, ".", color = purple)
plt.plot(wavelength_a1, field_factor_a1, ".", color = 'k')

plt.yscale('log')
plt.xlabel('Wavelength in vacuo (nm)')
plt.ylabel('Field enhancement factor $\\eta$(-)')
plt.xlim(200,800)
plt.ylim(0.1,200)

plt.legend()