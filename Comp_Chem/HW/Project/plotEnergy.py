#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Name: plotEnergy.py - Version 1.0
# Author: Cody R. Drisko (crdrisko)
# Date: 09/29/2019-09:40:39
# Description: Create 3D plot from the single-point energies of SO2

import numpy as np
import matplotlib.pyplot as plt
from sys import argv
from mpl_toolkits import mplot3d
import scipy.interpolate

if argv[2] == "SO2":
    energyData = np.loadtxt(argv[1], dtype=float, comments='#')

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

    fig, ax = plt.subplots(1, 1, figsize=(6, 6), subplot_kw={'projection': '3d'})
    ax.scatter3D(lengths, angles, energy)
    ax.scatter3D(optLen, optAng, lowestEnergy, color='r',\
    label="Energy: %0.3f Hartree\nLength: %s $\\AA$\n  Angle: %s$\\degree$" %(lowestEnergy, optLen, optAng))
    ax.set_xlabel("S-O Bond Length ($\\AA$)")
    ax.set_ylabel("O-S-O Angle (Degrees)")
    ax.set_zlabel("\n\n\n\nSingle-Point Energies\n(Hartrees)")
    ax.legend()

    plt.savefig("SO2-Energies.png")

elif argv[2] == "Acetaldehyde":
    ### Results of the Scanning Technique ###
    data_scan = np.loadtxt(argv[1], dtype=float, comments='#')

    N_scan = np.size(data_scan)
    angle = data_scan[0:N_scan:1, 0]
    energy = data_scan[0:N_scan:1, 1]

    plt.figure(1)
    plt.plot(angle, energy, 'o')

    plt.xlabel("Dihedral Angle (Degrees)")
    plt.ylabel("Energy (Hartrees)")

    plt.savefig("Acetaldehyde-Energies.png")
