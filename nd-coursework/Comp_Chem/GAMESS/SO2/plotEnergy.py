#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Name: plotEnergy.py - Version 1.0
# Author: Cody R. Drisko (crdrisko)
# Date: 09/29/2019-09:40:39
# Description: Create 3D plots of the single-point energies of SO2

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import scipy.interpolate

energyData = np.loadtxt("allEnergies.dat", dtype=float)

N = np.size(energyData)

lengths = energyData[0:N:1, 0]
angles = energyData[0:N:1, 1]
energy = energyData[0:N:1, 2]

Lengths, Angles = np.meshgrid(lengths, angles)
Energy = scipy.interpolate.griddata((lengths, angles), energy, (lengths[None,:], angles[:,None]))

for i in range(0, np.size(energy)):
    if energy[i] == np.min(energy):
        lowestEnergy = energy[i]
        optLen = lengths[i]
        optAng = angles[i]

fig = plt.figure(figsize=plt.figaspect(0.5))
ax = fig.add_subplot(1, 2, 1, projection='3d')
ax.scatter3D(lengths, angles, energy)
ax.scatter3D(optLen, optAng, lowestEnergy, color='r')
ax.set_xlabel("S-O Bond Length ($\\AA$)")
ax.set_ylabel("O-S-O Angle (Degrees)")
ax.set_zlabel("\n\n\n\nSingle-Point Energies\n(Hartrees)")

ax = fig.add_subplot(1, 2, 2)

ax.contourf(Lengths, Angles, Energy)
ax.plot(optLen, optAng, 'ro', label="Energy: %0.3f Hartree\nLength: %s $\\AA$\n  Angle: %s$\\degree$"
        %(lowestEnergy, optLen, optAng))
ax.set_xlabel("S-O Bond Length ($\\AA$)")
ax.set_ylabel("O-S-O Angle (Degrees)")
ax.legend()

plt.subplots_adjust(left=0.1, right=0.95, wspace=0.75, hspace=0.1)
plt.savefig("Energy-Plot.png")
