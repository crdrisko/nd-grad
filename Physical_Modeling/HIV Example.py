#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created: Thu Jul 12 21:35:52 2018

Author: crdrisko

Description: First computer lab (Python for Physical Modeling): HIV Example
"""

import numpy as np
import matplotlib.pyplot as plt

## 4.1.1 Explore the model

time = np.linspace(0,7,100)
A = 100000
B = 75000
alpha = 0.5
beta = 1

viral_load = A * np.exp(-alpha*time) + B * np.exp(-beta*time)

plt.plot(time, viral_load, label = 'Model Data')

## 4.1.2 Fit Experimental Data

data_file = "/Users/crdrisko/.spyder-py3/Example_Data/HIVseries.csv"
hiv_data = np.loadtxt(data_file, delimiter= ',')

N = np.size(hiv_data)
t = hiv_data[0:N:1, 0]          # time since treatment (days)
C = hiv_data[0:N:1, 1]          # concentration of virus 

ax = plt.gca()
ax.set_title("HIV Concentration vs. Time", size = 16, weight = 'bold')
ax.set_xlabel("Time since treatment (days)", weight = 'bold')
ax.set_ylabel("Concentration of virus", weight = 'bold')

plt.plot(t,C, 'o', label = 'Experimental Data')
plt.legend()
