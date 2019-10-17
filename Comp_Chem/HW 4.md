# Homework 4 - Cody R. Drisko

## Question 1)

a) From **Table 1.1** we can see that the bond lengths of the equilibrium structures match our chemical intuition for what these should be. The shortest bonds in both structures belongs to the molecules actually bonded to H<sub>1</sub>, while the longest distance occur between the H<sub>1</sub> atom and whatever it isn't bonded to. For the C - C and C - O bonds, it is easy to see that the bond length shortens when the atoms are double bonded to each other.

b) For both acetaldehyde and vinyl alcohol, I ran geometry optimizations using the default Quadratic Approximation algorithm followed by a quick optimization of that structure using the Quasi-Newton Raphson algorithm to verify the results. Each run was done in cartesian coordinates with a guessed Hessian. The number of steps was set to 50 and the convergence tolerance was 0.0001 Hartree/Bohr. The sample input files are shown in **Code 1.1**.

c) The results of the vibrational spectrum calculation are shown in **Figure 1.1**. Each calculation was run using the input shown in **Code 1.2** and the Hessian eigenvalues were all positive, telling me we are in fact at the minima for these structures.

d) The results of the single point energy calculations are shown in **Table 1.2**. The sample input file used is shown in **Code 1.3** and the code to do the conversions and scaling required for these calculations is shown in **Code 1.4**.

e)

**Code 1.1:** Sample GAMESS input file for geometry optimization calculations of acetaldehyde and vinyl alcohol.

```FORTRAN
 $CONTRL SCFTYP=RHF RUNTYP=OPTIMIZE DFTTYP=B3LYP ICHARG=0 MULT=1 COORD=CART $END
 $STATPT METHOD=QA(NR) OPTTOL=0.0001 HESS=GUESS NSTEP=50 $END
 $BASIS GBASIS=N31 NGAUSS=6 NDFUNC=1 $END
 $DATA
 ...
 $END
```

**Code 1.2:** Sample GAMESS input file for vibrational frequency calculations of acetaldehyde and vinyl alcohol.

```FORTRAN
 $CONTRL SCFTYP=RHF RUNTYP=HESSIAN DFTTYP=B3LYP ISPHER=1 COORD=CART $END
 $BASIS GBASIS=N31 NGAUSS=6 NDFUNC=1 $END
 $FORCE METHOD=SEMINUM $END
 $DATA
 ...
 $END
```

**Code 1.3:** Sample GAMESS input file for single-point energy calculations of acetaldehyde and vinyl alcohol.

```FORTRAN
 $CONTRL SCFTYP=RHF MPLEVL=2 RUNTYP=ENERGY ICHARG=0 MULT=1 COORD=CART $END
 $BASIS GBASIS=N31 NGAUSS=6 NDFUNC=1 $END
 $DATA
 ...
 $END
```

**Code 1.4:** Python script to convert and scale the energies from the GAMESS output files.

```Python
#!/usr/bin/env python3
# Name: convertEnergy.py - Version 1.0.0
# Author: Cody R. Drisko (crdrisko)
# Date: 10/17/2019-07:53:00
# Description: Convert and scale GAMESS energies to kJ/mol

import numpy as np
import matplotlib.pyplot as plt

energyInput = float(input("Enter the energy in Hartrees: "))
modelInput = input("Enter the model used in the calculation: ")

energyOutput = energyInput * (627.509 * 4.184 / 1000)    ## Hartrees --> kJ/mol

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
```

**Table 1.1:** Internal Coordinates of some of the bonds in the Acetaldehyde and Vinyl Alcohol structures. Lenghts in parentheses denote non-bonded distances.

| | **Acetaldehyde** | **Transition State** | **Vinyl Alcohol** |
|:---|:---:|:---:|:---:|
| **H1 - C (&#8491;)** | 1.093   |  | (2.485) |
| **C - C (&#8491;)**  | 1.509   |  | 1.334   |
| **C - O (&#8491;)**  | 1.211   |  | 1.363   |
| **O - H1 (&#8491;)** | (2.581) |  | 0.972   |

**Table 1.2:** Single-Point Energy calculations of Acetaldehyde and Vinyl Alcohol using the MP2/6-31G(d) level theory. ZPE's were scaled by 0.9613 as they were calculated using B3LYP, while the other energies were scaled by 0.9434 as they were calculated using MP2.

| | **Product - Reactant (kJ/mol)** | **TS - Reactant (kJ/mol)** |
|:---|:---:|:---:|
| **Base Calc**    | 0.0669415 | - (-378.7527539102831) |
| **MP2/6-31G(d)** | 0.0659842 | - (-379.8234172337006) |
| **ZPE**          | 2.1641901‬ | - 140.9380454251‬ |
| **MP2 + ZPE**    | 2.2301743‬ |  |

---

<div style="page-break-after: always;"></div>

## Question 2)

a)

**Code 2.1:** Sample GAMESS input file for single-point energy calculations of acetaldehyde while scanning around the H<sub>1</sub>CCO dihedral.

```FORTRAN
 
```

---

<div style="page-break-after: always;"></div>

## Question 3)

a)

b)

c)

d)

---

<div style="page-break-after: always;"></div>

## Question 4)

a)

b)

c)

---

<div style="page-break-after: always;"></div>

## Question 5)

a) 

---
