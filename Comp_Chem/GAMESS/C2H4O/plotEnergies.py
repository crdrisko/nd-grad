#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Name: plotEnergies.py - Version 1.0.0
# Author: Cody R. Drisko (crdrisko)
# Date: 10/18/2019-08:02:13
# Description: Plotting the relevant data for HW 4

import numpy as np
import matplotlib.pyplot as plt


### Results of the Vibrational Analysis ###
data_va = np.loadtxt("vinylAlcohol/vinylAlcohol_spec.jdx", dtype=float, comments='#')

N_va = np.size(data_va)
frec_va = data_va[0:N_va:1, 0]
int_va = data_va[0:N_va:1, 1]

data_ts = np.loadtxt("TS/TS_spec.jdx", dtype=float, comments='#')

N_ts = np.size(data_ts)
frec_ts = data_ts[0:N_ts:1, 0]
int_ts = data_ts[0:N_ts:1, 1]

data_a = np.loadtxt("acetaldehyde/acetaldehyde_spec.jdx", dtype=float, comments='#')

N_a = np.size(data_a)
frec_a = data_a[0:N_a:1, 0]
int_a = data_a[0:N_a:1, 1]


plt.figure(1)
plt.plot(frec_a, int_a, label="Acetaldehyde")
plt.plot(frec_ts, int_ts, label="Transition State")
plt.plot(frec_va, int_va, label="Vinyl Alcohol")

plt.xlabel("Scaled Frequencies (cm$^-1$) ")
plt.ylabel("Intensities")
plt.legend()
plt.savefig("Frequencies.pdf")



### Results of the Scanning Technique ###
data_scan = np.loadtxt("scan/allEnergies.dat", dtype=float)

N_scan = np.size(data_scan)
angle = data_scan[0:N_scan:1, 0]
energy = data_scan[0:N_scan:1, 1]


plt.figure(2)
plt.plot(angle, energy, label="Acetaldehyde")

plt.xlabel("Dihedral Angle (Degrees)")
plt.ylabel("Energy (Hartrees)")
plt.legend()
plt.savefig("Energies.pdf")