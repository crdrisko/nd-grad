#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Wed Apr 10 12:14:20 2019

Author: crdrisko

Description: Plots of the extinction cross sections of gold nanoparticles, with diameters 10 and 30 nm.
    Ref: 1) "Field Enhancement around Metal Nanoparticles and Nanoshells: A Systematic Investigation"
            by Katsuaki Tanabe.
        
         2) "'Naked' Gold Nanoparticles: Synthesis, Characterization, Catalytic Hydrogen Evolution,
            and SERS" by Getahun Merga, Nuvia Saucedo, Laura C. Cass, James Puthussery, and Dan Meisel.
"""

import numpy as np
import matplotlib.pyplot as plt

### Fit Function from Literature ###

     ## Wavelengths ##
lambda_short1 = np.linspace(250,500,251)
lambda_long1  = np.linspace(501,2000,1500)
lambda_short2 = np.linspace(250,500,251)
lambda_long2  = np.linspace(501,2000,1500)
     
     ## Parameters ##
          # Epsilon 1 @ small wavelengths #
a6 =  2.987199e-13
a5 = -7.960874e-10
a4 =  8.519635e-7
a3 = -4.712248e-4
a2 =  1.425147e-1
a1 = -2.239051e1
a0 =  1.429313e3
          # Epsilon 1 @ long wavelengths # 
b6 =  1.862162e-16
b5 = -1.286561e-12
b4 =  3.440482e-9
b3 = -4.480664e-6
b2 =  2.912960e-3
b1 = -9.423524e-1
b0 =  1.217245e2
          # Epsilon 2 @ small wavelengths #
c6 =  1.353837e-12
c5 = -2.999955e-9
c4 =  2.726629e-6
c3 = -1.300071e-3
c2 =  3.425863e-1
c1 = -4.723584e1
c0 =  2.664003e3
          # Epsilon 2 @ long wavelengths #
d6 =  1.656867e-17
d5 = -1.420149e-13
d4 =  4.945864e-10
d3 = -8.912814e-7
d2 =  8.801682e-4
d1 = -4.439847e-1
d0 =  8.958838e1

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
eps_1_tot[0:50:1] = eps_1_sw[0]
eps_1_tot[50:301:1] = eps_1_sw
eps_1_tot[301:1801:1] = eps_1_lw

eps_2_tot = np.zeros(1801)
eps_2_tot[0:50:1] = eps_2_sw[0]
eps_2_tot[50:301:1] = eps_2_sw
eps_2_tot[301:1801:1] = eps_2_lw

wavelength = np.zeros(1801)
wavelength[0:50:1] = np.linspace(200,249,50)
wavelength[50:301:1] = lambda_short1
wavelength[301:1801:1] = lambda_long1

epsilon = eps_1_tot + 1j*eps_2_tot
epsilon_m = 1.5**2

k = (2 * np.pi * np.sqrt(epsilon_m)) / wavelength

a_1 = 10/2                    # Particle size in nm
a_2 = 30/2                    # Particle size in nm

C_abs1  = 4 * np.pi * k * a_1**3 * (np.imag((epsilon - epsilon_m)/(epsilon + 2*epsilon_m)))
C_scat1 = (8 * np.pi / 3) * k**4 * a_1**6 * (((epsilon - epsilon_m)/(epsilon + 2*epsilon_m)) \
          * np.conjugate((epsilon - epsilon_m)/(epsilon + 2*epsilon_m)))
C_ext1  = C_scat1 + C_abs1

C_abs2  = 4 * np.pi * k * a_2**3 * (np.imag((epsilon - epsilon_m)/(epsilon + 2*epsilon_m)))
C_scat2 = (8 * np.pi / 3) * k**4 * a_2**6 * (((epsilon - epsilon_m)/(epsilon + 2*epsilon_m)) \
          * np.conjugate((epsilon - epsilon_m)/(epsilon + 2*epsilon_m)))
C_ext2  = C_scat2 + C_abs2

plt.figure("Figure 1")
plt.plot(wavelength, np.real(C_ext1)/1e14, label = 'Extinction - 10 nm particle')
plt.plot(wavelength, np.real(C_abs1)/1e14, label = 'Absorption - 10 nm particle')
plt.plot(wavelength, np.real(C_scat1)/1e14, label = 'Scattering - 10 nm particle')

plt.xlabel('Wavelength (nm)')
plt.ylabel('Extinction Cross Section ($cm^2$)')
plt.xlim(200,950)

plt.legend()

plt.figure("Figure 2")
plt.plot(wavelength, np.real(C_ext2)/1e14, label = 'Extinction - 30 nm particle')
plt.plot(wavelength, np.real(C_abs2)/1e14, label = 'Absorption - 30 nm particle')
plt.plot(wavelength, np.real(C_scat2)/1e14, label = 'Scattering - 30 nm particle')

plt.xlabel('Wavelength (nm)')
plt.ylabel('Extinction Cross Section ($cm^2$)')
plt.xlim(200,950)

plt.legend()


