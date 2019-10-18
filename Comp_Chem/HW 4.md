# Homework 4 - Cody R. Drisko

## Question 1)

a) From **Table 1.1** we can see that the bond lengths of the equilibrium structures match our chemical intuition for what these should be. The shortest bonds in both structures belongs to the molecules actually bonded to H<sub>1</sub>, while the longest distance occur between the H<sub>1</sub> atom and whatever it isn't bonded to. For the C - C and C - O bonds, it is easy to see that the bond length shortens when the atoms are double bonded to each other.

b) The acetaldehyde optimization was trivial to perform. I optimized the molecule using a Quadratic Approximation algorithm and then verified the results using a Quasi-Newton Raphson algorithm. Vinyl Alcohol proved to be more difficult than I anticipated and required a Quadratic Approximation, Quasi-Newton Raphson, and Ration Function Optimization algorithm before the vibrational spectra finally reflected a true energy minima. In all cases, the tollarance was set to 0.0001, the hessian was guessed, and the number of steps used was 50. The template I used for these optimizations is shown in **Code 1.1**.

*c) Both the optimized structured of acetaldehyde and vinyl alcohol were at true minima as the eigenvalues of their Hessians were all positive. For vinyl alcohol, the only way I could get the vibration calculation to succeed was by recognizing that the molecule had CS symmetry and locking it there.*

d) The results of the single point energy calculations are shown in **Table 1.2**. As we would expect, the Product - Reactant energy will be related to the enthalpy of the reaction and the TS - Reactant energy will be related to the Gibbs free energy or activation energy of the barrier.

e) The reaction enthalpy at 298K, H(298), is roughly 73.6263 kJ/mol. Thus, the reaction is endothermic and we need to supply energy to the system to go from acetaldehyde to vinyl alcohol.

**Code 1.1:** Sample GAMESS input file for a Geometry Optimization.

```FORTRAN
 $CONTRL SCFTYP=RHF RUNTYP=OPTIMIZE DFTTYP=B3LYP ICHARG=0 MULT=1 COORD=CART $END
 $STATPT METHOD=(QA/NR/RFO) OPTTOL=0.0001 HESS=GUESS NSTEP=50 $END
 $BASIS GBASIS=N31 NGAUSS=6 NDFUNC=1 $END
 $DATA
Title Geometry Optimization
C1 1 
...
 $END
```

**Table 1.1:** Internal Coordinates of some of the bonds in the Acetaldehyde and Vinyl Alcohol structures. Lenghts in parentheses denote non-bonded distances.

| | **Acetaldehyde** | **Transition State** | **Vinyl Alcohol** |
|:---|:---:|:---:|:---:|
| **H1 - C (&#8491;)** | 1.093   | (1.524) | (2.485) |
| **C - C (&#8491;)**  | 1.509   | 1.412   | 1.335   |
| **C - O (&#8491;)**  | 1.211   | 1.285   | 1.363   |
| **O - H1 (&#8491;)** | (2.581) | (1.291) | 0.972   |

**Table 1.2:** Single-Point Energy calculations of Acetaldehyde and Vinyl Alcohol using the MP2/6-31G(d) level theory. ZPE's were scaled by 0.9613 as they were calculated using B3LYP through a vibrational analysis.

| | **Product - Reactant (kJ/mol)** | **TS - Reactant (kJ/mol)** |
|:---|:---:|:---:|
| **Base Calc**    | 70.9577 | 383.5188 |
| **MP2/6-31G(d)** | 69.9423 | 318.0305 |
| **ZPE**          |  2.1630 | -13.6643 |
| **MP2 + ZPE**    | 72.1053 | 304.3662 |

---

<div style="page-break-after: always;"></div>

## Question 2)

a)

---

<div style="page-break-after: always;"></div>

## Question 3)

a) For the transition state, the results in **Table 1.1** show that this structure is indeed an intermediate between the reactant and product. The distances for the C - O and C - C bonds lie between a double and single bond, and the H<sub>1</sub> atom is not bonded to either the carbon or oxygen as it is transitioning between the two.

b) The single imaginary mode for this transition state occurs at a scaled frequency of 2110.28 cm<sup>-1</sup> and has an intensity of 8.9561. From the animation on WebMO, we can see that this vibration corresponds to the motion of the hydrogen atom from the carbon atom to the oxygen parallel to the C - C bond.

c) The results of my calculations are shown in **Table 1.2** and intutivly these values make sense. The Product - Reactant energy corresponds to the enthalpy of the reaction and should be noticiably lower than the TS - Reactant energy. That energy corresponds to the activation energy or Gibbs free energy of the Transition state.

*d) The value of &#x394;G&#8225; at 298K is 291.8822 kJ/mol. In the TST expression, this corresponds to a rate constant of*

---

<div style="page-break-after: always;"></div>

## Question 4)

a)

b)

c)

---

<div style="page-break-after: always;"></div>

## Question 5)

a) As we can see from **Table 5.1**, the energy difference is large in vinyl alcohol than it is in acetaldehyde to exite the molecule to the first excited state. This also means the wavelength of light required for this transition is shorter for vinyl alcohol. 

**Table 5.1:** Energy differences and wavelengths from the CIS/6-31G(d) excited state calculations for Acetaldehyde and Vinyl Alcohol. 

| | **Acetaldehyde** | **Vinyl Alcohol** |
|:---:|:---:|:---:|
| **Energy Difference (Hartrees)** | 0.1830 | 0.3096 |
| **Wavelength of Light (nm)**     | 249.03669 | 147.1988 |

---
