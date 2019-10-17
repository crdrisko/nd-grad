# Homework 3 - Cody R. Drisko

## Question 1)

a) There are 16 primitive Gaussians and 12 total basis functions included in this calculation. These are split up among the s, p, and d orbitals accordingly:

* s: 6 Primitive Gaussians in one basis set shell.
* p: 10 Primitive Gaussians in three basis set shells.
* d: 0 Primitive Gaussians.

b) The number of SCF iterations required to converge was 12 for this calculation.

c) The final energy of the Ar atom was -524.4520526614 Hartrees.

d) The energies for each of the orbitals are shown in **Table 1.1** below. The identities of the occupied orbitals in Argon from lowest energy to highest are: 1s, 2s, 2p, 3s, 3p.

e) From **Table  1.1**, we can see that the total HFS energy and all orbital energies are lower in the FDA calculation than in the GAMESS calculation. Ultimately though, I’d say the agreement between the two methods is actually pretty good.

**Code 1.1:** GAMESS input file for argon atom undergoing a single-point energy calculation with HFS.

```FORTRAN
!   File created by the GAMESS Input Deck Generator Plugin for Avogadro
 $BASIS GBASIS=N31 NGAUSS=6 $END
 $CONTRL RUNTYP=ENERGY DFTTYP=SLATER $END

 $DATA
Title Ar single-point calculation
C1
Ar    18.0     0.0     0.0     0.0
 $END
```

**Table 1.1:** Total and orbital energies of the argon atom calculated using GAMESS and FDA.

| **Energy Type** | **GAMESS**         | **FDA**            |
|:---------------:|:------------------:|:------------------:|
| **E_tot**       | -524.4521 Hartrees | -526.8275 Hartrees |
| **E_1s**        | -113.6768 Hartrees | -116.9366 Hartrees |
| **E_2s**        | -10.7172 Hartrees  | -11.6037 Hartrees  |
| **E_2p**        | -8.3677 Hartrees   | -9.2721 Hartrees   |
| **E_3s**        | -0.8218 Hartrees   | -1.1022 Hartrees   |
| **E_3p**        | -0.3222 Hartrees   | -0.5735 Hartrees   |

---

## Question 2)

a) The spin multiplicity of SO<sub>2</sub> is singlet, because there are no unpaired electrons.

* Multiplicity = 2 * (S=0) + 1 = 1

b) The calculation used 48 primitive Gaussians and 49 total basis functions.

c) It took 22 cycles before the energy calculation converged.

d) Even though we didn't specify it, it looks like by default the SCF algorithm used by GAMESS is Restrictive Hartree-Fock (RHF): `SCFTYP=RHF`.

e) The final total energy of the SO<sub>2</sub> molecule is -548.2422757249 Hartrees.

f) The energy of the HOMO is -0.2837 Hartrees and the energy of the LUMO is -0.1546 Hartrees. The molecule has a total of 16 occupied orbitals.

g) The final dipole moment of the molecule is 1.508668 Debyes. Compared to the [experimental value](https://doi.org/10.1063/1.437860) of 1.63305 Debyes, this calculation was off. Potentially the coordinates I picked for this molecule are causing it to under-calculate the dipole moment.

h) The gross charges on each atom of the SO<sub>2</sub> molecule are shown in **Table 2.1**. Based on the fact that the charges on oxygens are not equal and that the Mulliken estimation is based on the geometry of the molecule, it is safe to say that the molecule is not properly symmetric.

i) We can see the electrostatic potential of the SO<sub>2</sub> molecule in **Figure 2.1**. The blue (positive) end on the sulfur atom corresponds to the *electrophilic*  end, while the red (negative) ends on each of the oxygen atoms corresponds to the *nucleophilic* end.

**Code 2.1:** GAMESS input file for a sulfur dioxide molecule undergoing a single-point energy calculation with GGA.

```FORTRAN
!   File created by the GAMESS Input Deck Generator Plugin for Avogadro
 $BASIS GBASIS=PCSEG-1 $END
 $CONTRL RUNTYP=ENERGY DFTTYP=PBE ISPHER=1 MULT=1 $END

 $DATA
Title SO2 single-point calculation
C1
O     8.0    -5.66692     3.47856     1.63888
S    16.0    -4.73071     2.43709     1.33794
O     8.0    -3.44983     2.74004     0.76414
 $END
```

<div style="page-break-after: always;"></div>

**Table 2.1:** Mulliken gross charges for each atom in the SO<sub>2</sub> molecule.

| **Atom** | **Mulliken Charge** |
|:--------:|:-------------------:|
| **S**    |  0.597301 e         |
| **O**    | -0.297110 e         |
| **O**    | -0.300192 e         |

**Figure 2.1:** Electrostatic potential of the SO<sub>2</sub> molecule mapped onto a Van der Waals surface.

![alt text](GAMESS/SO2/SO2.png "Electrostatic Potential of SO2")

---

<div style="page-break-after: always;"></div>

## Question 3

a) Shown in **Codes 3.1**, **3.2**, and **3.3** are the template for the GAMESS input, bash script to run the calculation, and python script to plot the energies as a function of bond length and angle, respectively. The results from the calculations are shown in **Figure 3.1**. The lowest energy (-548.249 Hartrees) occurs at a S-O bond distance of 1.50 &#8491; and a O-S-O angle of 120.0&#176;.

b) According to the optimization run (**Code 3.4**), the optimal bond distances for the S-O bond is 1.491 &#8491;, and the optimal angle for the O-S-O angle is 118.5&#176;. Considering the bond angles and lengths were varied by 5 units each time in part a, we actually got pretty close. This optimization was much faster but ultimately, the two methods agree.

**Code 3.1:** Template for each of the runs that will attempt to optimize the energy of the SO<sub>2</sub> molecule by minimizing the energy. Here, 'LEN' will be replaced by values between 1.30 and 1.70 &#8491;, and 'ANG' will be replaced by values between 90.0 and 150.0&#176;.

```FORTRAN
 $BASIS GBASIS=PCSEG-1 $END
 $CONTRL COORD=ZMT ISPHER=1 RUNTYP=ENERGY DFTTYP=PBE MULT=1 $END

 $DATA
Title SO2 single-point calculation template with Z-Matrix
C1
S
O 1 LEN
O 1 LEN 2 ANG
 $END
```

<div style="page-break-after: always;"></div>

**Code 3.2:** Bash script to run "optimization" calculations on the CRC. Note: I had too many jobs running in the queue already, so I couldn't submit them to the CRC queue.

```Bash
#!/bin/bash
# Name: runGAMESS.sh - Version 1.0
# Author: Cody R. Drisko (crdrisko)
# Date: 09/29/2019-08:45:51
# Description: Run GAMESS jobs on the CRC

modifyFiles()       #@ DESCRIPTION: Modify a file using sed
{                   #@ USAGE: modifyFiles fileName oldString newString
  sed "s/${2?}/${3?}/g" ${1?} > tempFile && mv tempFile ${1?}
}

lengths=(1.30 1.35 1.40 1.45 1.50 1.55 1.60 1.65 1.70 1.75)
angles=(90 95 100 105 110 115 120 125 130 135 140 145 150)

for len in ${lengths[@]}
do
  mkdir ${len}-A
  cd ${len}-A

  for ang in ${angles[@]}
  do
    mkdir ${ang}-deg
    cd ${ang}-deg

    cp ../../SO2_temp.inp SO2.inp

    modifyFiles SO2.inp LEN $len
    modifyFiles SO2.inp ANG $ang

    rungms SO2.inp > SO2.out

    energyArray=( $(grep FINAL\ R-PBE\ ENERGY\ IS SO2.out) )
    energy=${energyArray[4]}

    printf "%s\t %s\t %s\n" $len $ang $energy >> ../../allEnergies.dat

    cd ../
  done
  cd ../
done
```

<div style="page-break-after: always;"></div>

**Code 3.3:** Python code to plot the results of the calculations. These plots are shown in **Figure 3.1**.

```Python
#!/usr/bin/env python3
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
```

**Code 3.4:** GAMESS input file for the optimization of the SO<sub>2</sub> molecule.

```FORTRAN
!   File created by the GAMESS Input Deck Generator Plugin for Avogadro
 $BASIS GBASIS=PCSEG-1 $END
 $CONTRL RUNTYP=OPTIMIZE DFTTYP=PBE ISPHER=1 MULT=1 $END

 $DATA
Title SO2 Geometry Optimization
C1
O     8.0    -5.66692     3.47856     1.63888
S    16.0    -4.73071     2.43709     1.33794
O     8.0    -3.44983     2.74004     0.76414
 $END
```

**Figure 3.1:** Plots of the energy represented by a 3D scatter plot and a contour plot. The red point in both graphs is the structure with the lowest energy.

![alt text](GAMESS/SO2/Energy-Plot.png "Manual Optimization of the SO2 Molecule")

---

<div style="page-break-after: always;"></div>

## Question 4

| **AO<sub>2</sub>** | **A-O (&#8491;)** | **O-A-O (Degrees)** | **Spin Multiplicity** | **Dipole Moment (e&#8491;)** | **Mulliken Charge A (e)** | **Mulliken Charge O (e)**|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **CO<sub>2</sub>**  | 1.176 | 180.0 | Singlet | 3.0605x10<sup>-5</sup> | 0.519821 | -0.25991 |
| **NO<sub>2</sub>**  | 1.211 | 133.8 | Doublet | 5.3310x10<sup>-2</sup> | 0.390296 | -0.19515 |
| **SiO<sub>2</sub>** | 1.541 | 180.0 | Singlet | 1.9383x10<sup>-4</sup> | 0.859985 | -0.43000 |
| **SO<sub>2</sub>**  | 1.491 | 118.5 | Singlet | 3.6960x10<sup>-1</sup> | 0.656766 | -0.32839 |

**Code 4.1:** GAMESS input file for the optimization of the CO<sub>2</sub> molecule.

```FORTRAN
!   File created by the GAMESS Input Deck Generator Plugin for Avogadro
 $BASIS GBASIS=PCSEG-1 $END
 $CONTRL RUNTYP=OPTIMIZE DFTTYP=PBE ISPHER=1 MULT=1 $END

 $DATA
Title CO2 Geometry Optimization
C1
C     6.0    -0.98864     2.41193     0.00106
O     8.0     0.49420     2.38807     0.10884
O     8.0    -2.43756     2.41127    -0.12043
 $END
```

**Code 4.2:** GAMESS input file for the optimization of the NO<sub>2</sub> molecule. Note: I couldn't get the results to converge when I drew the molecule in Avogadro like the others so I used a Z-matrix for this one.

```FORTRAN
!   File created by the GAMESS Input Deck Generator Plugin for Avogadro
 $BASIS GBASIS=PCSEG-1 $END
 $CONTRL COORD=ZMT SCFTYP=ROHF ISPHER=1 RUNTYP=OPTIMIZE MULT=2 DFTTYP=PBE $END

 $DATA
Title NO2 Geometry Optimization
C1
N
O 1 1.20
O 1 1.20 2 132
 $END
```

<div style="page-break-after: always;"></div>

**Code 4.3:** GAMESS input file for the optimization of the SiO<sub>2</sub> molecule.

```FORTRAN
!   File created by the GAMESS Input Deck Generator Plugin for Avogadro
 $BASIS GBASIS=PCSEG-1 $END
 $CONTRL RUNTYP=OPTIMIZE DFTTYP=PBE ISPHER=1 MULT=1 $END

 $DATA
Title SiO2 Geometry Optimization
C1
Si    14.0    -4.00518     4.13005     0.00435
O     8.0    -2.90553     3.21368     0.03161
O     8.0    -5.31866     3.55234    -0.00743
 $END
```

**Code 4.4:** GAMESS input file for the optimization of the SO<sub>2</sub> molecule.

```FORTRAN
!   File created by the GAMESS Input Deck Generator Plugin for Avogadro
 $BASIS GBASIS=PCSEG-1 $END
 $CONTRL RUNTYP=OPTIMIZE DFTTYP=PBE ISPHER=1 MULT=1 $END

 $DATA
Title SO2 Geometry Optimization
C1
O     8.0    -5.66692     3.47856     1.63888
S    16.0    -4.73071     2.43709     1.33794
O     8.0    -3.44983     2.74004     0.76414
 $END
```

---
