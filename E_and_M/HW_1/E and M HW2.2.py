#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Fri Feb  1 09:21:46 2019

Author: crdrisko

Description: Snell's law plot of light entering BK7 glass at an incidence angle of 60 degrees 
and getting scattered at different angles. BK7 data retrieved from:

    https://refractiveindex.info/?shelf=glass&book=BK7&page=SCHOTT
"""

import numpy as np
import matplotlib.pyplot as plt

n_inc = 1.0
n_700 = 1.5131                                          # Red: 620-750 nm
n_600 = 1.5163                                          # Orange: 590-620 nm
n_580 = 1.5171                                          # Yellow: 570-590 nm
n_525 = 1.5199                                          # Green: 495-570 nm
n_475 = 1.5232                                          # Blue: 450-495 nm
n_400 = 1.5308                                          # Violet: 380-450 nm

theta_inc = np.pi/3

R_theta_ref= np.arcsin((n_inc * np.sin(theta_inc))/n_700)
O_theta_ref= np.arcsin((n_inc * np.sin(theta_inc))/n_600)
Y_theta_ref= np.arcsin((n_inc * np.sin(theta_inc))/n_580)
G_theta_ref= np.arcsin((n_inc * np.sin(theta_inc))/n_525)
B_theta_ref= np.arcsin((n_inc * np.sin(theta_inc))/n_475)
V_theta_ref= np.arcsin((n_inc * np.sin(theta_inc))/n_400)


# Plotting

color1 = "#ffa500"
color2 = "#800080"
color3 = "#ffff00"

x1 = np.linspace(-1,0,5)
x2 = np.linspace(0,1,5)
x3 = np.linspace(.98,1,5)

fig, ax1 = plt.subplots()

left, bottom, width, height = [0.75, 0.265, 0.15, 0.15]
ax2 = fig.add_axes([left, bottom, width, height])


ax1.plot(x1, -np.tan(theta_inc)*x1, 'k', x2, (-np.tan(R_theta_ref))**-1*x2, 'r', 
         x2, (-np.tan(O_theta_ref))**-1*x2, color1, x2, (-np.tan(Y_theta_ref))**-1*x2, 'y', 
         x2, (-np.tan(G_theta_ref))**-1*x2, 'g', x2, (-np.tan(B_theta_ref))**-1*x2, 'b', 
         x2, (-np.tan(V_theta_ref))**-1*x2, color2)
ax2.plot(x3, (-np.tan(R_theta_ref))**-1*x3, 'r', 
         x3, (-np.tan(O_theta_ref))**-1*x3, color1, x3, (-np.tan(Y_theta_ref))**-1*x3, color3, 
         x3, (-np.tan(G_theta_ref))**-1*x3, 'g', x3, (-np.tan(B_theta_ref))**-1*x3, 'b', 
         x3, (-np.tan(V_theta_ref))**-1*x3, color2)

ax2.set_yticklabels([])
ax2.set_xticklabels([])
ax2.axes.get_yaxis().set_ticks([])
ax2.axes.get_xaxis().set_ticks([])

ax1.spines['left'].set_position('zero')
ax1.spines['bottom'].set_position('zero')

ax1.spines['right'].set_color('none')
ax1.spines['top'].set_color('none')

plt.show()
