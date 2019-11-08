#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Name: runO2.py - Version 1.0.0
# Author: Cody R. Drisko (crdrisko)
# Date: 11/07/2019-21:32:10
# Description: Script to run the VASP calculations for questions 4 and 5 on a O2 molecule

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


if argv[1] == "Q4":
	o2 = Atoms( [ Atom('O',[  0, 0, 0]),
              	      Atom('O',[1.25, 0, 0]) ],
              	      cell=(12, 12, 12) )

	o2.center()

	calc = Vasp('molecules/geometry-o2',  
	       xc = 'PBE',  # the exchange-correlation functional
            encut = 400,    # planewave cutoff
           ismear = 0,      # Gaussian smearing
            sigma = 0.01,   # very small smearing factor for a molecule
              nsw = 20,     # Number of ionic steps
           ibrion = 1,      # Quasi-Newton Raphson 
            ispin = 2,      # Turn spin polarization on
	    atoms = o2)

	calc.calculate()
elif argv[1] == "Q5":
	o2 = Atoms( [ Atom('O',[  0, 0, 0]),
              	      Atom('O',[1.23378, 0, 0]) ],
              	      cell=(12, 12, 12) )

	o2.center()

	calc = Vasp('molecules/vibration-o2',  
	       xc = 'PBE',  ## The exchange-correlation functional
            encut = 400,    ## Planewave cutoff
           ismear = 0,      ## Gaussian smearing
            sigma = 0.01,   ## Very small smearing factor for a molecule
              nsw = 20,     ## Number of ionic steps
           ibrion = 6,      ## Finite-differences frequency calculation
	    nfree = 2, 	    ## Positive and negative step directions
	    potim = 0.010,  ## Step size in Ang
            ispin = 2,      ## Turn spin polarization on
	    atoms = o2)

	calc.calculate()

