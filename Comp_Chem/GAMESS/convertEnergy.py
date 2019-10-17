#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Name: convertEnergy.py - Version 1.0.0
# Author: Cody R. Drisko (crdrisko)
# Date: 10/17/2019-07:53:00
# Description: Convert and scale GAMESS energies to kJ/mol

import numpy as np
import matplotlib.pyplot as plt

energyInput = float(input("Enter the energy in Hartrees: "))
modelInput = input("Enter the model used in the calculation: ")

energyOutput = energyInput * (627.509 * 4.184 / 1000) 				## Hartrees --> kJ/mol

if modelInput == "HF/3-21G":
	scaleFactor = 0.9085
elif modelInput == "HF/6-31G(d)":
	scaleFactor = 0.8929
elif modelInput == "MP2/6-31G(d)":
	scaleFactor = 0.9434
elif modelInput == "B3LYP/6-31G(d)":
	scaleFactor = 0.9613
else:
	print("Not one of the pre-selected models. Energy value will remain unscaled.")
	scaleFactor = 1.0

energyOutput *= scaleFactor
print("Converted Energy: %s kJ/mol" %energyOutput)
