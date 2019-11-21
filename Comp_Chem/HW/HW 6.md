# Homework 6 - Cody R. Drisko and Garrett Tow

*NOTE*: The metals we were tasked with analyzing were Cu, Ag, and Au. All calculations, input/output files, and code can be found in my GitHub repository located [here](https://github.com/crdrisko/ND-Coursework).

## Question 1)

a) From **Table 1.1** below, we can see that the electron configurations for our metals match what we would expect. Cu, Ag, and Au all belong to the 11th group on the periodic table meaning that they should have similar chemical properties (i.e. electron configurations). What we see is that rather than fill the last s-orbital for each metal, which is what we would expect according to the Mandelung rule (Aufbau Principle), the metals stabilize their nearly filled d-orbitals by taking that last electron from the s. Thus, all electron configurations end with: (n)d<sup>10</sup> (n+1)s<sup>1</sup>.

**Table 1.1:** Electron configurations for the metal atoms (in order of increasing energy).

| **Metal** | **Electron Configuration** |
|:----------|:---------------------------|
| **Cu**    | 1s<sup>2</sup> 2s<sup>2</sup> 2p<sup>6</sup> 3s<sup>2</sup> 3p<sup>6</sup> 3d<sup>10</sup> 4s<sup>1</sup> |
| **Ag**    | 1s<sup>2</sup> 2s<sup>2</sup> 2p<sup>6</sup> 3s<sup>2</sup> 3p<sup>6</sup> 3d<sup>10</sup> 4s<sup>2</sup> 4p<sup>6</sup> 4d<sup>10</sup> 5s<sup>1</sup> |
| **Au**    | 1s<sup>2</sup> 2s<sup>2</sup> 2p<sup>6</sup> 3s<sup>2</sup> 3p<sup>6</sup> 3d<sup>10</sup> 4s<sup>2</sup> 4p<sup>6</sup> 4d<sup>10</sup> 5s<sup>2</sup> 4f<sup>14</sup> 5p<sup>6</sup> 5d<sup>10</sup> 6s<sup>1</sup> |

**Code 1.1:** Python code used to run VASP calculations for the metal atoms: Cu, Ag, and Au.

```Python
## VASP, ASE, and Python Packages ##

VASPRC['queue.q'] = 'long'
VASPRC['queue.nprocs'] = 24
VASPRC['queue.pe'] = 'mpi-24'

for metal in ['Cu', 'Ag', 'Au']:
    ## Question 1 - Single Metal Atoms ##
    metal_atom = Atoms( [ Atom(metal, [0, 0, 0]) ],
                          cell=(8, 9, 10) )
    metal_atom.center()

    calc = Vasp('%s/%s-atom' %(metal, metal),
            xc = 'PBE',     ## the exchange-correlation functional
        ismear = 1,         ## Methfessel-Paxton smearing
         encut = 400,       ## energy cutoff
         atoms = metal_atom)

    calc.calculate()
```

---

<div style="page-break-after: always;"></div>

## Question 2)

a) Plotted in **Figure 2.1**, we can see the energies of each of our metals converges to a differnece of 0.02 eV between 7 and 9 k-points. For Au, it actually doesn't converge to the selected tollerance until between 9 and 11 k-points, but it is close to convergence at 7. I think the most reliable and cost effective number of k-points is 9 for these three metals. The code for this analysis is shown in both **Code 2.1** and **Code 2.2**.

**Figure 2.1:** Convergence of the energy for the Cu, Ag, and Au metals as we varied the number of k-points in the grid.

![alt text](../VASP/Metals/images/metal-kpt-convergence.png "Metal Energy Convergence")

**Code 2.1:** Bash script to grab the energies from OUTCAR files, calculate the energy differences and use Python (**Code 2.2**) to plot the energies.

```bash
#!/bin/bash

for metal in Cu Ag Au
do
  for dir in $metal/$metal-kpt-convergence/kpt-{3..11..2}
  do
      energyArray=( $(grep TOTEN $dir/OUTCAR | tail -n 1) )

    if [ ${dir##*-} -ne 3 ]
    then
      lastEnergy=( $(grep $((${dir##*-} - 2)) $metal/energies.dat  | tail -n 1) )
      echo ${dir##*-} ${energyArray[4]} $( echo "${lastEnergy[1]} - ${energyArray[4]}" | bc ) >> $metal/energies.dat
    else
      echo ${dir##*-} ${energyArray[4]} 0 > $metal/energies.dat
    fi
  done
done

python3 runMetals.py Plot
```

<div style="page-break-after: always;"></div>

**Code 2.2:** Python code used to run VASP calculations for the metal atoms: Cu, Ag, and Au.

```Python
## VASP, ASE, and Python Packages ##

VASPRC['queue.q'] = 'long'
VASPRC['queue.nprocs'] = 24
VASPRC['queue.pe'] = 'mpi-24'

for metal in ['Cu', 'Ag', 'Au']:
    ## Question 2 - k-point Convergence ##
    kPoints = [3, 5, 7, 9, 11]

    for k in kPoints:
        metal_cubic = bulk(metal, 'fcc', cubic = True)

        calc = Vasp('%s/%s-kpt-convergence/kpt-%s' %(metal, metal, k),
                xc = 'PBE',
            ismear = 1,
             encut = 400,
             kpts = [k,k,k],
             atoms = metal_cubic)

        calc.calculate()

### Plotting ###
if argv[1] == "Plot":
    data_Cu = np.loadtxt("Cu/energies.dat", dtype=float)
    N_Cu= np.size(data_Cu)
    kpoints_Cu = data_Cu[0:N_Cu:1, 0]
    energies_Cu = data_Cu[0:N_Cu:1, 1]

    data_Ag = np.loadtxt("Ag/energies.dat", dtype=float)
    N_Ag = np.size(data_Ag)
    kpoints_Ag = data_Ag[0:N_Ag:1, 0]
    energies_Ag = data_Ag[0:N_Ag:1, 1]

    data_Au = np.loadtxt("Au/energies.dat", dtype=float)
    N_Au = np.size(data_Au)
    kpoints_Au = data_Au[0:N_Au:1, 0]
    energies_Au = data_Au[0:N_Au:1, 1]

    plt.plot(kpoints_Cu, energies_Cu, 'ro-', label="Cu Metal")
    plt.plot(kpoints_Ag, energies_Ag, 'go-', label="Ag Metal")
    plt.plot(kpoints_Au, energies_Au, 'bo-', label="Au Metal")
    plt.xlabel("k-Points")
    plt.ylabel("Total Energy (eV)")
    plt.ylim(-15.5, -9.5)
    plt.legend()
    plt.savefig('images/metal-kpt-convergence.png')
    plt.show()
```

---

<div style="page-break-after: always;"></div>

## Question 3)

a) [ref](https://onlinelibrary.wiley.com/doi/pdf/10.1002/9783527633296.app5)

---

<div style="page-break-after: always;"></div>

## Question 4)

a)

---

<div style="page-break-after: always;"></div>

## Question 5)

a)

---

<div style="page-break-after: always;"></div>

## Question 6)

a)

---

<div style="page-break-after: always;"></div>

## Question 7)

a)
