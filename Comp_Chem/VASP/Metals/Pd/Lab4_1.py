#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Name: Lab4_2.py - Version 1.0.0
# Author: Cody R. Drisko (crdrisko)
# Date: 11/20/2019-21:20:07
# Description: First question from Lab 4 - Bulk Systems


### Packages ###
import numpy as np
import matplotlib.pyplot as plt
from sys import argv

from ase.eos import EquationOfState
from vasp.vasprc import VASPRC
from ase.build import bulk
from vasp import *
from ase.visualize import view


### Run Calculations ###
if argv[1] == "Bulk"
	## Creating a Bulk System ##
	
	# a is the lattice constant in Angstroms
	Pd_cubic = bulk('Pd', 'fcc', a = 3.89, cubic = True)
	view(Pd_cubic)
	print(Pd_cubic)

	Pd_ortho = bulk('Pd', 'fcc', a = 3.89, orthorhombic = True)
	view(Pd_ortho)
	print(Pd_ortho)

	Pd_primitive = bulk('Pd', 'fcc') # if a is not specified, default experimental value is used
	view(Pd_primitive)
	print(Pd_primitive)

	## Energies vs. Lattice Constants ##
	VASPRC['queue.q'] = '*long'
	VASPRC['queue.nprocs'] = 24
	VASPRC['queue.pe'] = 'mpi-24'

	# Generate an array of 7 points 10% around 3.89 angstroms
	A = np.linspace(3.89 * 0.9, 3.89 * 1.1, 7)

	for a in A:
		# We will use the cubic cell for simplicity
		Pd_cubic = bulk('Pd', 'fcc', a = a, cubic = True)

		calc = Vasp('EOS/Pd-a-{0:1.2f}'.format(a),
			xc = 'PBE',
			encut = 400,
			ismear = 1, 	# Use MP smearing for metals
			kpts = [8,8,8],
			atoms = Pd_cubic)

		calc.calculate()


### Plotting the Results of Our Calculations ###
elif argv[1] == "Plot":
	data = np.loadtxt("energies.dat", dtype=float)
	
	N = np.size(data)
	lattice = data[0:N:1, 0]
	energies = data[0:N:1, 1]
	volumes = data[0:N:1, 2]
	
	plt.figure(1)		
	plt.plot(lattice, energies, 'bo-')
	plt.xlabel('Lattice constant ($\AA$)')
	plt.ylabel('Total energy (eV)')
	plt.savefig('EOS/images/Pd-fcc-lattice.png')
	plt.show()
	
	# Let's fit this to an equation of state

	eos = EquationOfState(volumes, energies, eos='birchmurnaghan')
	v0, e0, b = eos.fit()
	a0 = v0**(1/3)
	eos.plot(filename='EOS/images/Pd-EOS.png', show=True)

	print('Minimum Energy = {0:1.3f} eV'.format(e0))
	print('Optimal Volume = {0:1.3f} cubic angstroms'.format(v0))
	print('Optimal lattice constant = {0:1.3f} angstroms'.format(a0))

