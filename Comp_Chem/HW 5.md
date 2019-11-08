# Homework 5 - Cody R. Drisko 

*NOTE*: All calculations, input/output files, and code can be found in my GitHub repository located [here](https://github.com/crdrisko/ND-Coursework). I probably should have mentioned this for the previous homeworks as well, but it slipped my mind. Additionally, running the ASE calculations (get_potential_energy, get_number_of_electrons, etc.) would give me NAN or NONE whenever I attempted to run the commands. I believe this was due to the simulations not being complete when these functions were called, so there was nothing to print out. Instead of trying to get ASE to work, I chose to just use `grep` or look through the output files myself to get the results I needed.

## Question 1) 

*NOTE:* For quesion 1, the VASP calculations were run through the python script shown in **Code 1.2** and analysis was done using the bash script in **Code 1.1**. All the results collected in the OUTCAR file were run through grep.

a) The total number of electrons for our argon atom is 18 and 8 of those are the valence electrons.

b) The final converged potential energy is -0.03061587 eV.  

c) The number of SCF Iterations is also located in the OUTCAR file, in this case it took 8 SCF cycles.

d) All of the results are collected in **Table 1.1**. From the OUTCAR file, we can find the energies of the core orbitals. These core orbitals are the 1s, 2s, and 2p orbitals which is easy to see from the immensely low energies. From the EIGENVAL file, we see that the lowest, valence orbital is the 3s orbital, followed by the 3p. After those two orbitals it gets a little more complicated. The OUTCAR file suggests that the next orbital is a 3d orbital when based on past knowledge, this should be a higher energy orbital than both the 4s and 4p orbitals. The degeneracy of the orbital suggests it is an s orbital, but so would the next one, so at this point it is difficult to label the unoccupied orbitals.

e) The total number of plane-waves used (basis functions) is 110592.

<div style="page-break-after: always;"></div>

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
from sys import argv  ## All VASP packages would go here (see Code 3.1)

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

a) The code responsible for running these calculations is shown in **Code 3.1**. The final potential energy I got was -.023647819 eV.

b) The magnetic moment was 0.0001, telling me something about this calculation was off. Since the oxygen atom has two unpaired electrons, we'd expect the magnetic moment to be 2.0. 

c) The results of these calcualtions are shown in **Table 3.1** for the up-spin electrons and **Table 3.2** for the down-spin electrons. Because the magnetic moment didn't make much sense of oxygen, I'd expect these occupancies to be off too. I'd have to try some other input flags and parameters to see if I couldn't get the calculation where I think it should be (i.e. a magnetic moment of 2).

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

<div style="page-break-after: always;"></div>

**Table 3.1:** The energies and occupancies of the spin up orbitals in Oxygen according to the VASP calculations.

| **Orbital** | **Energy (eV)** | **Occupancy** |
|:-----------:|:---------------:|:-------------:|
| **1**       | -23.938312      | 1.0           |
| **2**       |  -8.999771      | 1.980027      |
| **3**       |  -0.268874      | 0.0           |
| **4**       |   0.654605      | 0.0           |
| **5**       |   0.875371      | 0.0           |

**Table 3.2:** The energies and occupancies of the spin down orbitals in Oxygen according to the VASP calculations.

| **Orbital** | **Energy (eV)** | **Occupancy** |
|:-----------:|:---------------:|:-------------:|
| **1**       | -23.938375      |  1.0          |
| **2**       |  -9.000030      |  2.019972     |
| **3**       |  -0.283293      |  0.0          |
| **4**       |   0.603358      |  0.0          |
| **5**       |   0.853088      |  0.0          |

---

<div style="page-break-after: always;"></div>

## Question 4)

a) The code to run these calculations is shown in **Code 4.1**. The geometry did converge. We know this because it took less than the max of 20 itterations to reach a final energy value.

b) The optimization process took a total of 5 relaxation steps to reach convergence. This was because I gave the bond distance a good starting place r<sub>o-o</sub> = 1.25 &#8491;.

c) The final converged energy was -9.8646607 eV.

d) The magnetic moment was 2.0, which makes sense for an O<sub>2</sub> molecule because it has two unpaired electrons so the magnetic moment should be: spin up - spin down = 2 - 0 = 2. 

e) The results of these calcualtions are shown in **Table 4.1** for the up-spin electrons and **Table 4.2** for the down-spin electrons.

**Table 4.1:** The energies and occupancies of the spin up orbitals in the oxygen molecule according to the VASP calculations.

| **Orbital** | **Energy (eV)** | **Occupancy** |
|:-----------:|:---------------:|:-------------:|
| **1**       | -32.530725      | 1.0           |
| **2**       | -20.653480      | 1.0           |
| **3**       | -13.421133      | 1.0           |
| **4**       | -13.271592      | 2.0           |
| **5**       |  -6.950344      | 2.0           |
| **6**       |  -0.285442      | 0.0           |
| **7**       |   0.526091      | 0.0           |
| **8**       |   0.650309      | 0.0           |
| **9**       |   0.784557      | 0.0           |
| **10**      |   0.902852      | 0.0           |
| **11**      |   0.987004      | 0.0           |
| **12**      |   1.508039      | 0.0           |
| **13**      |   1.722727      | 0.0           |

<div style="page-break-after: always;"></div>

**Table 4.2:** The energies and occupancies of the spin down orbitals in the oxygen molecule according to the VASP calculations.

| **Orbital** | **Energy (eV)** | **Occupancy** |
|:-----------:|:---------------:|:-------------:|
| **1**       | -31.303873      | 1.0           |
| **2**       | -18.857591      | 1.0           |
| **3**       | -12.493961      | 1.0           |
| **4**       | -11.428004      | 2.0           |
| **5**       |  -4.676721      | 2.0           |
| **6**       |  -0.190586      | 0.0           |
| **7**       |   0.723523      | 0.0           |
| **8**       |   0.751510      | 0.0           |
| **9**       |   0.869296      | 0.0           |
| **10**      |   0.931394      | 0.0           |
| **11**      |   1.031969      | 0.0           |
| **12**      |   1.652687      | 0.0           |
| **13**      |   1.814724      | 0.0           |

<div style="page-break-after: always;"></div>

**Code 4.1:** Python script to run a geometry optimization and a vibrational frequency calculation in VASP on an O<sub>2</sub> molecule. The equilibrium/optimized bond length from the first calculation was used in the second.

```Python
import numpy as np
import matplotlib.pyplot as plt
from sys import argv  ## All VASP packages would go here (see Code 3.1)

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
elif argv[1] == "Q5":         ## Question 5 calculations
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

<div style="page-break-after: always;"></div>

## Question 5)

a) The code that ran these calculations is shown in **Code 4.1**. The computed vibrational frequency of the molecule is 1568.574328 cm<sup>-1</sup>. I found this value in the OUTCAR file with the following command: `grep cm Comp_Chem/VASP/O2/molecules/vibration-o2/OUTCAR`.

b) The ZPE for O<sub>2</sub> is just the frequency converted into an energy, ZPE = 1/2 h * c * v. For this molecule it was 0.097307 eV.

c) The ZPE corrected bond energy of O<sub>2</sub> is probably not going to give us a good answer since it involves the energy we calculated in question 3. The formula we can use is: Bond Energy = (2*E<sub>O</sub> - E<sub>O<sub>2</sub></sub> - ZPE) = 9.720058062 eV. This is way too high compared to the value of 5.165 eV according to [NIST](https://nvlpubs.nist.gov/nistpubs/Legacy/NSRDS/nbsnsrds31.pdf), but this is to be expected since our calculation in 3 was off. 
