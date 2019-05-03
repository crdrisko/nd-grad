#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Wed Apr 10 14:22:13 2019

Author: crdrisko

Description: Reprodution of the ref 2 plot. Rather than use Mie theory, the epsilon values and approximations
     are from a polynomial fit (ref 1) and Rayleigh scattering.
     
     Ref: 1) "Field Enhancement around Metal Nanoparticles and Nanoshells: A Systematic Investigation"
            by Katsuaki Tanabe.
        
          2) "Chain Length Dependence and Sensing Capabilities of the LocalizedSurface Plasmon Resonance
            of Silver Nanoparticles Chemically Modified with Alkanethiol Self-Assembled Monolayers"
            by Michelle Duval Malinsky, K. Lance Kelly, George C. Schatz, and Richard P. Van Duyne
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

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

n_N2 = 1.0
n_methanol = 1.33
n_benzene = 1.51
n_acetone = 1.359
n_ethanol = 1.362
n_CH2Cl2 = 1.424
n_SAM = 1.42

epsilon_N2  = n_N2**2                                      # Dielectric constants of different media
epsilon_met = n_methanol**2                           
epsilon_ben = n_benzene**2
epsilon_ace = n_acetone**2
epsilon_eth = n_ethanol**2
epsilon_chl = n_CH2Cl2**2

epsilon_Ag  = eps_1_tot + 1j*eps_2_tot                     # Dielectric constant of Ag nanoparticle
epsilon_SAM = n_SAM**2                                     # Dielectric constant of SAM

a_1 = 30                                                   # Radius of Ag nanoparticle (nm)
a_2 = a_1 + 2                                              # Radius of SAM + Ag nanoparticle (nm)
f = a_1/a_2

## Nitrogen Gas ##  
k_N2 = (2 * np.pi * np.sqrt(epsilon_N2)) / wavelength

beta_1_N2  = (epsilon_Ag - epsilon_N2) / (epsilon_Ag + 2*epsilon_N2)
beta_2_N2  = ((epsilon_SAM - epsilon_N2)*(epsilon_Ag + 2*epsilon_SAM) + (f**3)*(epsilon_Ag - epsilon_SAM)\
           * (epsilon_N2 + 2*epsilon_SAM)) / ((epsilon_SAM + 2*epsilon_N2)*(epsilon_Ag + 2*epsilon_SAM)  \
           + (f**3)*(2*epsilon_SAM - 2*epsilon_N2)*(epsilon_Ag - epsilon_SAM))

C_ext1_N2  = 4 * np.pi * k_N2 * a_1**3 * np.imag(beta_1_N2) + (8*np.pi/3) * k_N2**4 * a_1**6 \
           * (beta_1_N2 * np.conjugate(beta_1_N2))
C_ext2_N2  = 4 * np.pi * k_N2 * a_2**3 * np.imag(beta_2_N2) + (8*np.pi/3) * k_N2**4 * a_2**6 \
           * (beta_2_N2 * np.conjugate(beta_2_N2))
  
## Methanol ##         
k_met = (2 * np.pi * np.sqrt(epsilon_met)) / wavelength

beta_1_met = (epsilon_Ag - epsilon_met) / (epsilon_Ag + 2*epsilon_met)
beta_2_met = ((epsilon_SAM - epsilon_met)*(epsilon_Ag + 2*epsilon_SAM) + (f**3)*(epsilon_Ag - epsilon_SAM)\
           * (epsilon_met + 2*epsilon_SAM)) / ((epsilon_SAM + 2*epsilon_met)*(epsilon_Ag + 2*epsilon_SAM) \
           + (f**3)*(2*epsilon_SAM - 2*epsilon_met)*(epsilon_Ag - epsilon_SAM))

C_ext1_met = 4 * np.pi * k_met * a_1**3 * np.imag(beta_1_met) + (8*np.pi/3) * k_met**4 * a_1**6 \
           * (beta_1_met * np.conjugate(beta_1_met))
C_ext2_met = 4 * np.pi * k_met * a_2**3 * np.imag(beta_2_met) + (8*np.pi/3) * k_met**4 * a_2**6 \
           * (beta_2_met * np.conjugate(beta_2_met))

## Benzene ##  
k_ben = (2 * np.pi * np.sqrt(epsilon_ben)) / wavelength

beta_1_ben = (epsilon_Ag - epsilon_ben) / (epsilon_Ag + 2*epsilon_ben)
beta_2_ben = ((epsilon_SAM - epsilon_ben)*(epsilon_Ag + 2*epsilon_SAM) + (f**3)*(epsilon_Ag - epsilon_SAM)\
           * (epsilon_ben + 2*epsilon_SAM)) / ((epsilon_SAM + 2*epsilon_ben)*(epsilon_Ag + 2*epsilon_SAM) \
           + (f**3)*(2*epsilon_SAM - 2*epsilon_ben)*(epsilon_Ag - epsilon_SAM))

C_ext1_ben = 4 * np.pi * k_ben * a_1**3 * np.imag(beta_1_ben) + (8*np.pi/3) * k_ben**4 * a_1**6 \
           * (beta_1_ben * np.conjugate(beta_1_ben))
C_ext2_ben = 4 * np.pi * k_ben * a_2**3 * np.imag(beta_2_ben) + (8*np.pi/3) * k_ben**4 * a_2**6 \
           * (beta_2_ben * np.conjugate(beta_2_ben))


## Acetone ##  
k_ace = (2 * np.pi * np.sqrt(epsilon_ace)) / wavelength

beta_1_ace  = (epsilon_Ag - epsilon_ace) / (epsilon_Ag + 2*epsilon_ace)
beta_2_ace  = ((epsilon_SAM - epsilon_ace)*(epsilon_Ag + 2*epsilon_SAM) + (f**3)*(epsilon_Ag - epsilon_SAM)\
           * (epsilon_ace + 2*epsilon_SAM)) / ((epsilon_SAM + 2*epsilon_ace)*(epsilon_Ag + 2*epsilon_SAM)  \
           + (f**3)*(2*epsilon_SAM - 2*epsilon_ace)*(epsilon_Ag - epsilon_SAM))

C_ext1_ace  = 4 * np.pi * k_ace * a_1**3 * np.imag(beta_1_ace) + (8*np.pi/3) * k_ace**4 * a_1**6 \
           * (beta_1_ace * np.conjugate(beta_1_ace))
C_ext2_ace  = 4 * np.pi * k_ace * a_2**3 * np.imag(beta_2_ace) + (8*np.pi/3) * k_ace**4 * a_2**6 \
           * (beta_2_ace * np.conjugate(beta_2_ace))
  
## Ethanol ##         
k_eth = (2 * np.pi * np.sqrt(epsilon_eth)) / wavelength

beta_1_eth = (epsilon_Ag - epsilon_eth) / (epsilon_Ag + 2*epsilon_eth)
beta_2_eth = ((epsilon_SAM - epsilon_eth)*(epsilon_Ag + 2*epsilon_SAM) + (f**3)*(epsilon_Ag - epsilon_SAM)\
           * (epsilon_eth + 2*epsilon_SAM)) / ((epsilon_SAM + 2*epsilon_eth)*(epsilon_Ag + 2*epsilon_SAM) \
           + (f**3)*(2*epsilon_SAM - 2*epsilon_eth)*(epsilon_Ag - epsilon_SAM))

C_ext1_eth = 4 * np.pi * k_eth * a_1**3 * np.imag(beta_1_eth) + (8*np.pi/3) * k_eth**4 * a_1**6 \
           * (beta_1_eth * np.conjugate(beta_1_eth))
C_ext2_eth = 4 * np.pi * k_eth * a_2**3 * np.imag(beta_2_eth) + (8*np.pi/3) * k_eth**4 * a_2**6 \
           * (beta_2_eth * np.conjugate(beta_2_eth))

## Methylene Chloride ##  
k_chl = (2 * np.pi * np.sqrt(epsilon_chl)) / wavelength

beta_1_chl = (epsilon_Ag - epsilon_chl) / (epsilon_Ag + 2*epsilon_chl)
beta_2_chl = ((epsilon_SAM - epsilon_chl)*(epsilon_Ag + 2*epsilon_SAM) + (f**3)*(epsilon_Ag - epsilon_SAM)\
           * (epsilon_chl + 2*epsilon_SAM)) / ((epsilon_SAM + 2*epsilon_chl)*(epsilon_Ag + 2*epsilon_SAM) \
           + (f**3)*(2*epsilon_SAM - 2*epsilon_chl)*(epsilon_Ag - epsilon_SAM))

C_ext1_chl = 4 * np.pi * k_chl * a_1**3 * np.imag(beta_1_chl) + (8*np.pi/3) * k_chl**4 * a_1**6 \
           * (beta_1_chl * np.conjugate(beta_1_chl))
C_ext2_chl = 4 * np.pi * k_chl * a_2**3 * np.imag(beta_2_chl) + (8*np.pi/3) * k_chl**4 * a_2**6 \
           * (beta_2_chl * np.conjugate(beta_2_chl))


plt.figure('Figure 1')
plt.plot(wavelength,np.real(C_ext1_N2)/1e14,  color='b',label='Unmodified Ag in $N_2$')
plt.plot(wavelength,np.real(C_ext1_ace)/1e14, color='r', label='Unmodified Ag in acetone')
plt.plot(wavelength,np.real(C_ext1_chl)/1e14, color='g', label='Unmodified Ag in $CH_2Cl_2$')
plt.plot(wavelength,np.real(C_ext2_N2)/1e14, '--', color='b', label='Ag+SAM in $N_2$')
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

n_external = np.array([n_N2, n_methanol, n_acetone, n_ethanol, n_CH2Cl2, n_benzene])

for i in range(0,1800):
    if (np.amax(np.real(C_ext1_N2)) == C_ext1_N2[i]):
        lambda_max1_N2 = wavelength[i]
for i in range(0,1800):
    if (np.amax(np.real(C_ext2_N2)) == C_ext2_N2[i]):
        lambda_max2_N2 = wavelength[i]
for i in range(0,1800):
    if (np.amax(np.real(C_ext1_met)) == C_ext1_met[i]):
        lambda_max1_met = wavelength[i]
for i in range(0,1800):
    if (np.amax(np.real(C_ext2_met)) == C_ext2_met[i]):
        lambda_max2_met = wavelength[i]
for i in range(0,1800):
    if (np.amax(np.real(C_ext1_ace)) == C_ext1_ace[i]):
        lambda_max1_ace = wavelength[i]
for i in range(0,1800):
    if (np.amax(np.real(C_ext2_ace)) == C_ext2_ace[i]):
        lambda_max2_ace = wavelength[i]
for i in range(0,1800):
    if (np.amax(np.real(C_ext1_eth)) == C_ext1_eth[i]):
        lambda_max1_eth = wavelength[i]
for i in range(0,1800):
    if (np.amax(np.real(C_ext2_eth)) == C_ext2_eth[i]):
        lambda_max2_eth = wavelength[i]
for i in range(0,1800):
    if (np.amax(np.real(C_ext1_chl)) == C_ext1_chl[i]):
        lambda_max1_chl = wavelength[i]
for i in range(0,1800):
    if (np.amax(np.real(C_ext2_chl)) == C_ext2_chl[i]):
        lambda_max2_chl = wavelength[i]
for i in range(0,1800):
    if (np.amax(np.real(C_ext1_ben)) == C_ext1_ben[i]):
        lambda_max1_ben = wavelength[i]
for i in range(0,1800):
    if (np.amax(np.real(C_ext2_ben)) == C_ext2_ben[i]):
        lambda_max2_ben = wavelength[i]

peak_shift1_N2  = lambda_max1_N2  - lambda_max1_N2
peak_shift1_met = lambda_max1_met - lambda_max1_N2
peak_shift1_ace = lambda_max1_ace - lambda_max1_N2
peak_shift1_eth = lambda_max1_eth - lambda_max1_N2
peak_shift1_chl = lambda_max1_chl - lambda_max1_N2
peak_shift1_ben = lambda_max1_ben - lambda_max1_N2

peak_shift2_N2  = lambda_max2_N2  - lambda_max2_N2
peak_shift2_met = lambda_max2_met - lambda_max2_N2
peak_shift2_ace = lambda_max2_ace - lambda_max2_N2
peak_shift2_eth = lambda_max2_eth - lambda_max2_N2
peak_shift2_chl = lambda_max2_chl - lambda_max2_N2
peak_shift2_ben = lambda_max2_ben - lambda_max2_N2

LSPR1_data = np.array([peak_shift1_N2, peak_shift1_met, peak_shift1_ace, peak_shift1_eth, peak_shift1_chl, \
                       peak_shift1_ben])
LSPR2_data = np.array([peak_shift2_N2, peak_shift2_met, peak_shift2_ace, peak_shift2_eth, peak_shift2_chl, \
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