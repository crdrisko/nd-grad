#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (c) 2019-2025 Cody R. Drisko. All rights reserved.
# Licensed under the MIT License. See the LICENSE file in the project root for more information.
#
# Name: forceFieldGeneration12-6-4.py - Version 1.0.0
# Author: crdrisko
# Date: 09/24/2024-11:20:41
# Description:

import numpy as np
import matplotlib.pyplot as plt

### Classes and Functions ###
class AtomType:
    def __init__(self, name, sigma, epsilon, polarizability, C4_H2O=None):
        self.name = name
        self.sigma = sigma
        self.epsilon = epsilon
        self.polarizability = polarizability
        self.C4_H2O = C4_H2O

def calcC12(at1, at2):
    return (0.5 * (at1.sigma + at2.sigma))**12 * (4 * np.sqrt(at1.epsilon * at2.epsilon))

def calcC6(at1, at2):
    return (0.5 * (at1.sigma + at2.sigma))**6 * (4 * np.sqrt(at1.epsilon * at2.epsilon))

def calcC4(at1, at2):
    if (at2 is O_SPCE):
        return at1.C4_H2O
    elif ((at1 is at2) or (at2.C4_H2O is None)):
        return (at1.C4_H2O * at2.polarizability) / O_SPCE.polarizability
    else:
        return ((at2.C4_H2O * at1.polarizability) + (at1.C4_H2O * at2.polarizability)) / O_SPCE.polarizability

def calc12_6_4(at1, at2, r):
    return (calcC12(at1, at2) / r**12) + (-calcC6(at1, at2) / r**6) + (-calcC4(at1, at2)/ r**4)


### Main Code ###
polarizabilityConversionFactor = 0.1481847

Na     = AtomType("Na+", 1.472 * 2**(5/6), 0.03091095, 1 * polarizabilityConversionFactor, 6)       # J. Phys. B: At. Mol. Opt. Phys. 43 (2010) 202001
Cl     = AtomType("Cl-", 2.153 * 2**(5/6), 0.5240459, 3.235, -55)                                   # J. Phys. C: Solid State Phys., Vol. 11, 1978
Ca     = AtomType("Ca2+", 1.634 * 2**(5/6), 0.09731901, 3.262 * polarizabilityConversionFactor, 89) # J. Phys. B: At. Mol. Opt. Phys. 43 (2010) 202001
O_SPCE = AtomType("O_SPCE", 3.16549, 0.15532, 1.444)                                                # Eisenberg, D. S.; Kauzmann, W. The Structure and Properties of Water; OUP: Oxford, U.K., 1969.
CA     = AtomType("CA", 3.55, 0.068, 1.352)                                                         # J. Am. Chem. Soc., Vol. 112, No. 23, 1990
CB     = AtomType("CB", 3.55, 0.068, 1.896)                                                         # J. Am. Chem. Soc., Vol. 112, No. 23, 1990
HA     = AtomType("HA", 2.42, 0.03, 0.387)                                                          # J. Am. Chem. Soc., Vol. 112, No. 23, 1990

r = np.linspace(1e-9, 10, 10000)

for at1 in Na, Cl, Ca:
    for at2 in O_SPCE, Na, Cl, Ca, CA, CB, HA:
        print("  %s\t%s\tInversePowerSeries\t 12\t%0.5f\t6\t%0.5f\t4\t%0.5f" %(at1.name, at2.name, calcC12(at1, at2), -calcC6(at1, at2), -calcC4(at1, at2)))

    with plt.rc_context(fname='nd-grad/nd-research/scripts/spfResultParsing/custom.rc'):
        plt.plot(r, calc12_6_4(at1, at1, r), label="%s" %(at1.name))

plt.xlabel("$r$ ($\\AA$)")
plt.ylabel("$V_{LJ}$ (kcal/mol)")
plt.xlim(2, 10)
plt.ylim(-0.5, 0.5)
plt.legend()
plt.show()
