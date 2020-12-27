#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Name: runAr.py - Version 1.0.0
# Author: Cody R. Drisko (crdrisko)
# Date: 11/07/2019-19:00:38
# Description: Script responsible for running VASP calculations depending on the positional parameter passed to it

import numpy as np
import matplotlib.pyplot as plt
from sys import argv

from ase import Atoms, Atom
from ase.io import write
from ase.visualize import view
from vasp import *
from vasp.vasprc import VASPRC

VASPRC['queue.q'] = 'long'
VASPRC['queue.nprocs'] = 8
VASPRC['queue.pe'] = 'smp'

ar = Atoms( [ Atom('Ar', [0, 0, 0]) ],
              cell=(12, 12, 12) )

ar.center()

if argv[1] == "Q1":
	calc = Vasp('molecules/simple-ar',
               xc = 'PBE',    	## the exchange-correlation functional
           ismear = 0,        	## gaussian smearing
            sigma = 0.01,     	## very small smearing factor for a molecule
            atoms = ar)

	calc.calculate()
elif argv[1] == "Plot":
	data = np.loadtxt("energies.dat", dtype=float)

	N = np.size(data)
	cutoff = data[0:N:1, 0]
	energy = data[0:N:1, 1]
	time   = data[0:N:1, 2]

	plt.figure(1)
	plt.plot(cutoff, energy)
	plt.xlabel("Cutoff Energy (eV)")
	plt.ylabel("Potential Energy (eV)")
	plt.savefig("images/Argon-cutoff.png")

	plt.figure(2)
	plt.plot(cutoff, time)
	plt.xlabel("Cutoff Energy (eV)")
	plt.ylabel("Computational Cost/Elapsed Time (s)")
	plt.savefig("images/Argon-time.png") 
else:
	cutoff = int(argv[1])
	calc = Vasp('molecules/cutoff-ar-{0}'.format(cutoff),
		    xc = 'PBE',
		ismear = 0,
		 sigma = 0.01,
		 encut = cutoff,
		 atoms = ar)

	calc.calculate()
