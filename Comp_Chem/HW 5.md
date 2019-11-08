# Homework 5 - Cody R. Drisko 

## Question 1) 

*NOTE*: All calculations, input/output files, and code can be found in my GitHub repository located [here](https://github.com/crdrisko/ND-Coursework). I probably should have mentioned this for the previous homeworks as well but it slipped my mind. For quesion 1, the VASP calculations were run through the python script shown in **Code 1.2** and analysis was done using the bash script in **Code 1.1**. All the results collected in the OUTCAR file were run through grep.

a) The total number of electrons for our argon atom is 18 and 8 of those are the valence electrons.

b) The final converged potential energy is -0.03061587 eV.  

c) The number of SCF Iterations is also located in the OUTCAR file, in this case it took 8 SCF cycles.

d) All of the results are collected in **Table 1.1**. From the OUTCAR file, we can find the energies of the core orbitals. These core orbitals are the 1s, 2s, and 2p orbitals which is easy to see from the immensely low energies. From the EIGENVAL file, we see that the lowest, valence orbital is the 3s orbital, followed by the 3p. After those two orbitals it gets a little more complicated. The OUTCAR file suggests that the next orbital is a 3d orbital when based on past knowledge, this should be a higher energy orbital than both the 4s and 4p orbitals. The degeneracy of the orbital suggests it is an s orbital, but so would the next one, so at this point it is difficult to label the unoccupied orbitals.

e) The total number of plane-waves used (basis functions) is 110592.

**Table 1.1:** The energies and occupancies of the orbitals in Argon according to the VASP calculations.

| **Orbital** | **Energy (eV)** | **Occupancy** | **Core (y/n)** |
|:-----------:|:---------------:|:-------------:|:--------------:|
| **1s**      | -3120.2029      | 2             | y              |
| **2s**      | -296.9756       | 2             | y              |
| **2p**      | -229.8673       | 6             | y              |
| **3s**      | -24.182011      | 2             | n              |
| **3p**      | -10.160746      | 6             | n              |
| ***3d?***   | -0.322563       | 0             | n              |
| ***4s?***   | 0.631937        | 0             | n              |
| ***4p?***   | 0.881937        | 0             | n              |

<div style="page-break-after: always;"></div>

**Code 1.1:** Bash script to run VASP calculations for Argon atom using the python script in **Code 1.2**.

```bash
#!/bin/bash

## Question 1 ##
python runAr.py Q1            ## Run question 1's calculation
 
while true
do
  [ -f molecules/simple-ar/OUTCAR ] && break
done

sleep 5                       ## Let the job finish before analysis

for selection in NELECT TOTEN Iteration NPLWV
do
  echo "$selection:"
  grep $selection molecules/simple-ar/OUTCAR | tail -n 1
  echo
done


## Question 2 ##
for cutoff in 100 200 300 400 500
do
  python runAr.py $cutoff     ## Run question 2's calculations

  while true
  do
    [ -f molecules/cutoff-ar-$cutoff/OUTCAR ] && break
  done
  
  sleep 5                     ## Let the job finish before analysis

  energyArray=( $(grep TOTEN molecules/cutoff-ar-$cutoff/OUTCAR | tail -n 1) )
  timeArray=( $(grep Elapsed molecules/cutoff-ar-$cutoff/OUTCAR | tail -n 1) )
  echo "$cutoff ${energyArray[4]} ${timeArray[3]}" >> energies.dat
done

python runAr.py Plot          ## Plot the results
```

<div style="page-break-after: always;"></div>

**Code 1.2:** Python script responsible for running the VASP calculations depending on the positional parameter the bash script in **Code 1.1** passes to it.

```Python
import numpy as np
import matplotlib.pyplot as plt
from sys import argv          ## All VASP packages would go here (see Code 3.1)

ar = Atoms( [ Atom('Ar',[  0, 0, 0]) ],
             cell=(12, 12, 12) )

ar.center()

if argv[1] == "Q1":           ## Question 1 calculations
    calc = Vasp('molecules/simple-ar',
               xc = 'PBE',    ## the exchange-correlation functional
           ismear = 0,        ## gaussian smearing
            sigma = 0.01,     ## very small smearing factor for a molecule
            atoms = ar)

    calc.calculate()
elif argv[1] == "Plot":	      ## Plot the results from question 2
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
else:                         ## Question 2 calculations
    cutoff = int(argv[1])
    calc = Vasp('molecules/cutoff-ar-{0}'.format(cutoff),
            xc = 'PBE',
        ismear = 0,
         sigma = 0.01,
         encut = cutoff,
         atoms = ar)

    calc.calculate()
```

---

<div style="page-break-after: always;"></div>

## Question 2)

The bash and python scripts shown in **Code 1.1** and **Code 1.2**, respectively, ran all the necessary calculations for this question. Shown in **Figure 2.1** we can see how the potential energy changes as we vary the energy cutoff. Since our calculation in question 1 was done with a default cutoff energy of around 266 eV, we can see we didn't fully reach the converged value of roughly -0.025 eV. Looking at the actual values, we don't reach convergence within 0.005 eV until a cutoff of at least 300 eV. In **Figure 2.2** we see that the elapsed time rises pretty steadily as we increase the cutoff energy. It's a little difficult to see, but it seems to rise exponentially.

**Figure 2.1:** Plot of how the energy changes with respect to a changing cutoff energy. 

![alt text](VASP/AR/images/Argon-cutoff.png "Cutoff-Energy Plot")

<div style="page-break-after: always;"></div>

**Figure 2.2:** Plot of how the elapsed time changes with respect to a changing cutoff energy.

![alt text](VASP/AR/images/Argon-time.png "Cutoff-Time Plot")

---

<div style="page-break-after: always;"></div>

## Question 3)

a)

b)

c)

**Code 3.1:** Python script to run the Oxygen atom VASP calculation.

```Python
## All VASP/ASE Packages ##
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

o.center()                    ## Question 3 calculations

calc = Vasp('molecules/simple-o',
            xc = 'PBE',       ## the exchange-correlation functional
        ismear = 0,           ## gaussian smearing
         sigma = 0.01,        ## very small smearing factor for a molecule
         ispin = 2,           ## turn on spin polarization
         encut = 400,         ## energy cutoff
         atoms = o)

calc.calculate()
```

---

<div style="page-break-after: always;"></div>

## Question 4)

a)

b)

c)

d)

e)

<div style="page-break-after: always;"></div>

**Code 4.1:** Python script to run a geometry optimization and a vibrational frequency calculation in VASP on an O<sub>2</sub> molecule. The equilibrium/optimized bond length from the first calculation was used in the second.

```Python
import numpy as np
import matplotlib.pyplot as plt
from sys import argv          ## All VASP packages would go here (see Code 3.1)

VASPRC['queue.q'] = 'long'
VASPRC['queue.nprocs'] = 8
VASPRC['queue.pe'] = 'smp'

if argv[1] == "Q4":           ## Question 4 calculations
    o2 = Atoms( [ Atom('O',[  0, 0, 0]),
                  Atom('O',[1.25, 0, 0]) ],
                 cell=(12, 12, 12) )

    o2.center()

    calc = Vasp('molecules/geometry-o2',  
               xc = 'PBE',    ## The exchange-correlation functional
            encut = 400       ## Planewave cutoff
           ismear = 0,        ## Gaussian smearing
            sigma = 0.01,     ## Very small smearing factor for a molecule
              nsw = 20,       ## Number of ionic steps
           ibrion = 1,        ## Quasi-Newton Raphson 
            ispin = 2,        ## Turn spin polarization on
            atoms = o2)

    calc.calculate()
elif argv[1] == "Q5":		  ## Question 5 calculations
    o2 = Atoms( [ Atom('O',[  0, 0, 0]),
                  Atom('O',[1.23378, 0, 0]) ],
                 cell=(12, 12, 12) )

    o2.center()

    calc = Vasp('molecules/vibration-o2',  
               xc = 'PBE',    ## The exchange-correlation functional
            encut = 400,      ## Planewave cutoff
           ismear = 0,        ## Gaussian smearing
            sigma = 0.01,     ## Very small smearing factor for a molecule
              nsw = 20,       ## Number of ionic steps
           ibrion = 6,        ## Finite-differences frequency calculation
            nfree = 2,        ## Positive and negative step directions
            potim = 0.010,    ## Step size in Ang
            ispin = 2,        ## Turn spin polarization on
            atoms = o2)

    calc.calculate()
```

---

<div style="page-break-after: always;"></div>

## Question 5)

a)

b)

c)
