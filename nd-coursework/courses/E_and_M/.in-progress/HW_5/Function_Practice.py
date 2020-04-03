#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Mon Apr 15 11:45:26 2019

Author: crdrisko

Description: Same description as E_and_M_HW5.3.py but with functions instead of repeating the same
    code multiple times in a row.
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

### Functions ### 

def eps_fcn(lambda_fcn,a6,a5,a4,a3,a2,a1,a0):
    return a6*lambda_fcn**6 + a5*lambda_fcn**5 + a4*lambda_fcn**4 + a3*lambda_fcn**3 + \
        a2*lambda_fcn**2 + a1*lambda_fcn + a0   

def beta(epsilon_Ag,epsilon_m):
    return (epsilon_Ag - epsilon_m) / (epsilon_Ag + 2*epsilon_m)

def beta2(epsilon_SAM, epsilon_Ag, epsilon_m, f):        
    return ((epsilon_SAM - epsilon_m)*(epsilon_Ag + 2*epsilon_SAM) + (f**3)*(epsilon_Ag - epsilon_SAM) \
    * (epsilon_m + 2*epsilon_SAM)) / ((epsilon_SAM + 2*epsilon_m)*(epsilon_Ag + 2*epsilon_SAM) \
    + (f**3)*(2*epsilon_SAM - 2*epsilon_m)*(epsilon_Ag - epsilon_SAM))

def C_ext(k, a, beta):
    return 4 * np.pi * k * a**3 * np.imag(beta) + (8*np.pi/3) * k**4 * a**6 * (beta * np.conjugate(beta))

def lambda_max_finder(C_ext,wavelength):
    for i in range(0,1800):
        if (np.amax(np.real(C_ext)) == C_ext[i]):
            return wavelength[i]
    
### Fit Function from Literature ###

     ## Wavelengths ##
lambda_short1 = np.linspace(200,310,111)
lambda_long1  = np.linspace(311,2000,1690)
lambda_short2 = np.linspace(200,330,131)
lambda_long2  = np.linspace(331,2000,1670)
     
     ## Parameters ##
          # Epsilon 1 @ small wavelengths #
a6,a5,a4,a3,a2,a1,a0 = -1.308415e-11,1.764343e-8,-9.761668e-6,2.832725e-3,-.4538023,37.94213,-1.288348e3
          # Epsilon 1 @ long wavelengths # 
b6,b5,b4,b3,b2,b1,b0 = -2.037181e-17,1.183540e-13,-2.537882e-10,2.430043e-7,-1.420089e-4,8.990214e-4,8.526028
          # Epsilon 2 @ small wavelengths #
c6,c5,c4,c3,c2,c1,c0 =  3.636188e-11,-5.443344e-8,3.365273e-5,-1.100094e-2,2.005786,-193.4021,7.706263e3
          # Epsilon 2 @ long wavelengths #
d6,d5,d4,d3,d2,d1,d0 = -2.327098e-17,1.471828e-13,-3.635520e-10,4.530857e-7,-2.946733e-4,9.562290e-2,-11.49465

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

wavelength = np.zeros(1801)
wavelength[0:111:1] = lambda_short1
wavelength[111:1801:1] = lambda_long1

epsilon_nit = 1.0**2
epsilon_met = 1.33**2
epsilon_ben = 1.51**2
epsilon_ace = 1.359**2
epsilon_eth = 1.362**2
epsilon_chl = 1.424**2

epsilon_SAM = 1.42**2

epsilon_Ag = eps_1_tot + 1j*eps_2_tot

a_1 = 30                                                   # Radius of Ag nanoparticle (nm)
a_2 = a_1 + 2                                              # Radius of SAM + Ag nanoparticle (nm)
f = a_1/a_2

## Nitrogen ## 
k_nit = (2 * np.pi * np.sqrt(epsilon_nit)) / wavelength
beta1_nit = beta(epsilon_Ag,epsilon_nit)
beta2_nit = beta2(epsilon_SAM, epsilon_Ag, epsilon_nit, f)

C_ext1_nit = C_ext(k_nit, a_1, beta1_nit)
C_ext2_nit = C_ext(k_nit, a_2, beta2_nit)

## Methanol ## 
k_met = (2 * np.pi * np.sqrt(epsilon_met)) / wavelength
beta1_met = beta(epsilon_Ag,epsilon_met)
beta2_met = beta2(epsilon_SAM, epsilon_Ag, epsilon_met, f)

C_ext1_met = C_ext(k_met, a_1, beta1_met)
C_ext2_met = C_ext(k_met, a_2, beta2_met)

## Benzene ##  
k_ben = (2 * np.pi * np.sqrt(epsilon_ben)) / wavelength
beta1_ben = beta(epsilon_Ag,epsilon_ben)
beta2_ben = beta2(epsilon_SAM, epsilon_Ag, epsilon_ben, f)
  
C_ext1_ben = C_ext(k_ben, a_1, beta1_ben)
C_ext2_ben = C_ext(k_ben, a_2, beta2_ben)  

## Acetone ##  
k_ace = (2 * np.pi * np.sqrt(epsilon_ace)) / wavelength
beta1_ace = beta(epsilon_Ag,epsilon_ace)
beta2_ace = beta2(epsilon_SAM, epsilon_Ag, epsilon_ace, f)

C_ext1_ace = C_ext(k_ace, a_1, beta1_ace)
C_ext2_ace = C_ext(k_ace, a_2, beta2_ace)

## Ethanol ##         
k_eth = (2 * np.pi * np.sqrt(epsilon_eth)) / wavelength
beta1_eth = beta(epsilon_Ag,epsilon_eth)
beta2_eth = beta2(epsilon_SAM, epsilon_Ag, epsilon_eth, f)

C_ext1_eth = C_ext(k_eth, a_1, beta1_eth)
C_ext2_eth = C_ext(k_eth, a_2, beta2_eth)

## Methylene Chloride ##  
k_chl = (2 * np.pi * np.sqrt(epsilon_chl)) / wavelength
beta1_chl = beta(epsilon_Ag,epsilon_chl)
beta2_chl = beta2(epsilon_SAM, epsilon_Ag, epsilon_chl, f)

C_ext1_chl = C_ext(k_chl, a_1, beta1_chl)
C_ext2_chl = C_ext(k_chl, a_2, beta2_chl)


plt.figure('Figure 1')
plt.plot(wavelength,np.real(C_ext1_nit)/1e14,  color='b',label='Unmodified Ag in $N_2$')
plt.plot(wavelength,np.real(C_ext1_ace)/1e14, color='r', label='Unmodified Ag in acetone')
plt.plot(wavelength,np.real(C_ext1_chl)/1e14, color='g', label='Unmodified Ag in $CH_2Cl_2$')
plt.plot(wavelength,np.real(C_ext2_nit)/1e14, '--', color='b', label='Ag+SAM in $N_2$')
plt.plot(wavelength,np.real(C_ext2_ace)/1e14, '--', color='r', label='Ag+SAM in acetone')
plt.plot(wavelength,np.real(C_ext2_chl)/1e14, '--', color='g', label='Ag+SAM in $CH_2Cl_2$')

plt.xlabel('Wavelength (nm)')
plt.ylabel('Extinction Cross Section ($cm^2$)')
plt.xlim(200,600)

plt.legend()


plt.figure('Figure 2')
plt.plot(wavelength,np.real(C_ext1_met)/1e14, color='b', label='Unmodified Ag in methanol')
plt.plot(wavelength,np.real(C_ext1_eth)/1e14,  color='r',label='Unmodified Ag in ethanol')
plt.plot(wavelength,np.real(C_ext1_ben)/1e14, color='g', label='Unmodified Ag in benzene')
plt.plot(wavelength,np.real(C_ext2_met)/1e14, '--', color='b', label='Ag+SAM in methanol')
plt.plot(wavelength,np.real(C_ext2_eth)/1e14, '--', color='r', label='Ag+SAM in ethanol')
plt.plot(wavelength,np.real(C_ext2_ben)/1e14, '--', color='g', label='Ag+SAM in benzene')

plt.xlabel('Wavelength (nm)')
plt.ylabel('Extinction Cross Section ($cm^2$)')
plt.xlim(200,600)

plt.legend()

n_external = np.array([1.0, 1.33, 1.359, 1.362, 1.424, 1.51])


lambda_max1_nit = lambda_max_finder(C_ext1_nit,wavelength)
lambda_max2_nit = lambda_max_finder(C_ext2_nit,wavelength)

lambda_max1_met = lambda_max_finder(C_ext1_met,wavelength)
lambda_max2_met = lambda_max_finder(C_ext2_met,wavelength)

lambda_max1_ace = lambda_max_finder(C_ext1_ace,wavelength)
lambda_max2_ace = lambda_max_finder(C_ext2_ace,wavelength)

lambda_max1_eth = lambda_max_finder(C_ext1_eth,wavelength)
lambda_max2_eth = lambda_max_finder(C_ext2_eth,wavelength)

lambda_max1_chl = lambda_max_finder(C_ext1_chl,wavelength)
lambda_max2_chl = lambda_max_finder(C_ext2_chl,wavelength)

lambda_max1_ben = lambda_max_finder(C_ext1_ben,wavelength)
lambda_max2_ben = lambda_max_finder(C_ext2_ben,wavelength)

peak_shift1_nit = lambda_max1_nit - lambda_max1_nit
peak_shift1_met = lambda_max1_met - lambda_max1_nit
peak_shift1_ace = lambda_max1_ace - lambda_max1_nit
peak_shift1_eth = lambda_max1_eth - lambda_max1_nit
peak_shift1_chl = lambda_max1_chl - lambda_max1_nit
peak_shift1_ben = lambda_max1_ben - lambda_max1_nit

peak_shift2_nit = lambda_max2_nit - lambda_max2_nit
peak_shift2_met = lambda_max2_met - lambda_max2_nit
peak_shift2_ace = lambda_max2_ace - lambda_max2_nit
peak_shift2_eth = lambda_max2_eth - lambda_max2_nit
peak_shift2_chl = lambda_max2_chl - lambda_max2_nit
peak_shift2_ben = lambda_max2_ben - lambda_max2_nit

LSPR1_data = np.array([peak_shift1_nit, peak_shift1_met, peak_shift1_ace, peak_shift1_eth, peak_shift1_chl, \
                       peak_shift1_ben])
LSPR2_data = np.array([peak_shift2_nit, peak_shift2_met, peak_shift2_ace, peak_shift2_eth, peak_shift2_chl, \
                       peak_shift2_ben])

slopeA, interceptA, r_valueA, p_valueA, std_errA = stats.linregress(n_external, LSPR1_data)  
slopeB, interceptB, r_valueB, p_valueB, std_errB = stats.linregress(n_external, LSPR2_data)
    
plt.figure('Figure 3')  
plt.plot(n_external, LSPR1_data, marker="o", color='k', linestyle='None',label='A (Unmodified Ag)')
plt.plot(n_external, LSPR2_data, marker="D", color='k', linestyle='None',label ='B (Ag+SAM')
plt.plot(n_external, slopeA*n_external+interceptA, 'k', n_external, slopeB*n_external+interceptB, 'k')

plt.xlabel('Refractive Index of Surrounding Medium ($n_{external}$)')
plt.ylabel('LSPR Peak Shift from $N_2$ (nm)')

plt.xlim(1.0,1.6)
plt.ylim(0,100)

plt.legend()