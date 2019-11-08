#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Name: runO.py - Version 1.0.0
# Author: Cody R. Drisko (crdrisko)
# Date: 11/07/2019-21:32:00
# Description:

import numpy as np
import matplotlib.pyplot as plt

from ase import Atoms, Atom
from ase.io import write
from ase.visualize import view
from vasp import *
from vasp.vasprc import VASPRC

VASPRC['queue.q'] = 'long'
VASPRC['queue.nprocs'] = 8
VASPRC['queue.pe'] = 'smp'

o = Atoms( [ Atom('O', [0, 0, 0]) ],
              cell=(12, 12, 12) )

o.center()

calc = Vasp('molecules/simple-o',
            xc = 'PBE',    	## the exchange-correlation functional
        ismear = 0,        	## gaussian smearing
         sigma = 0.01,     	## very small smearing factor for a molecule
	 ispin = 2,		## turn on spin polarization
         encut = 400,		## energy cutoff
         atoms = o)

calc.calculate()
