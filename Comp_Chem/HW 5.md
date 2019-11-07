# Homework 5 - Cody R. Drisko

## Question 1) 

*NOTE:* None of the calc commands actually worked for me, they all gave nan or none, so the analysis of the files was done mainly using `grep` which I occasionally piped through `tail` to give me the last occurance of a value in the OUTCAR file.

a) The total number of electrons for our argon atom is 18 and 8 of those are the valence electrons. We can see this by running `grep NELECT OUTCAR`.

b) The final conserved potential energy is -0.03061587 eV. This is found by running `grep TOTEN OUTCAR | tail -n 1`.  

c) The number of SCF Iterations is also located in the OUTCAR file, in this case it took 8 SCF cycles. We can get the total number by running the following commands `grep Iteration OUTCAR | tail -n 1`.

d) From the OUTCAR file, we can find the energies of the core orbitals. These core orbitals are the 1s, 2s, and 2p orbitals which is easy to see from the immensely low energies. From the EIGENVAL file, we see that the lowest, valence orbital is the 3s orbital, followed by the 3p. After those two orbitals it gets a little more complicated. The OUTCAR file suggests that the next orbital is a 3d orbital when based on past knowledge, this should be a higher energy orbital than both the 4s and 4p orbitals. The degeneracy of the orbital suggests it is an s orbital, but so would the next one, so at this point it is difficult to label the unoccupied orbitals.

| **Orbital** | **Energy (eV)** | **Occupancy** | **Core (y/n)** |
|:-----------:|:---------------:|:-------------:|:--------------:|
| **1s**      | -3120.2029      | 2             | y              |
| **2s**      | -296.9756       | 2             | y              |
| **2p**      | -229.8673       | 6             | y              |
| **3s**      | -24.182011      | 2             | n              |
| **3p**      | -10.160746      | 6             | n              |
| ***3d?***    | -0.322563      | 0             | n              |
| ***4s?***     | 0.631937      | 0             | n              |
| ***4p?***     | 0.881937      | 0             | n              |

e) The total number of plane-waves used (basis functions) is 110592, which we can see by running the command: `grep NPLWV OUTCAR`.