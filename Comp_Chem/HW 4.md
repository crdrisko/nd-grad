# Homework 4 - Cody R. Drisko

## Question 1)

a) From **Table 1.1** we can see that the bond lengths of the equilibrium structures match our chemical intuition for what these should be. The shortest bonds in both structures belongs to the molecules actually bonded to H<sub>1</sub>, while the longest distance occur between the H<sub>1</sub> atom and whatever it isn't bonded to. For the C - C and C - O bonds, it is easy to see that the bond length shortens when the atoms are double bonded to each other.

b) For both acetaldehyde and vinyl alcohol, I ran geometry optimizations using the default Quadratic Approximation algorithm followed by a quick optimization of that structure using the Quasi-Newton Raphson algorithm to verify the results. Each run was done in cartesian coordinates with a guessed Hessian. The number of steps was set to 50 and the convergence tolerance was 0.0001 Hartree/Bohr. The sample input files are shown in **Code 1.1**.

c)

d)

e)

**Code 1.1:** GAMESS input file for the geometry optimization of acetaldehyde and vinyl alcohol.

```FORTRAN
 $CONTRL SCFTYP=RHF RUNTYP=OPTIMIZE DFTTYP=B3LYP ICHARG=0 MULT=1 COORD=CART $END
 $STATPT METHOD=QA(NR) OPTTOL=0.0001 HESS=GUESS NSTEP=50 $END
 $BASIS GBASIS=N31 NGAUSS=6 NDFUNC=1 $END
 $DATA
 ...
 $END
```

**Code 1.2:** GAMESS input file for vibrational frequency calculations of acetaldehyde and vinyl alcohol.

```FORTRAN

```

**Table 1.1:** Internal Coordinates of some of the bonds in the Acetaldehyde and Vinyl Alcohol structures. Lenghts in parentheses denote non-bonded distances.

| | **Acetaldehyde** | **Transition State** | **Vinyl Alcohol** |
|:---|:---:|:---:|:---:|
| **H1 - C (&#8491;)** | 1.093   |  | (2.485) |
| **C - C (&#8491;)**  | 1.509   |  | 1.334   |
| **C - O (&#8491;)**  | 1.211   |  | 1.363   |
| **O - H1 (&#8491;)** | (2.581) |  | 0.972   |

**Table 1.2:** Single-Point Energy calculations of Acetaldehyde and Vinyl Alcohol using the MP2/6-31G(d) level theory.

| | **Product - Reactant (kJ/mol)** | **TS - Reactant (kJ/mol)** |
|:---|:---:|:---:|
| **Base Calc**    |  |  |
| **MP2/6-31G(d)** |  |  |
| **ZPE**          |  |  |
| **MP2 + ZPE**    |  |  |

---

<div style="page-break-after: always;"></div>

## Question 2)