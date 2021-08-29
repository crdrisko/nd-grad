// Name: test.cpp
// Author: crdrisko
// Date: 07/28/2021-08:06:18
// Description:

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "atom.hpp"
#include "molecularEntity.hpp"
#include "molecule.hpp"
#include "rigidBody.hpp"

int main()
{
    MolecularEntityPtr SPCE    = std::make_shared<Molecule>("SPCE");
    MolecularEntityPtr SPCE_RB = std::make_shared<RigidBody>("SPCE_RB");

    SPCE->add(SPCE_RB);

    MolecularEntityPtr O_SPCE  = std::make_shared<Atom>("O", 0.0_Ang, 0.0_Ang, -0.06461_Ang);
    MolecularEntityPtr H1_SPCE = std::make_shared<Atom>("H", 0.0_Ang, 0.81649_Ang, 0.51275_Ang);
    MolecularEntityPtr H2_SPCE = std::make_shared<Atom>("H", 0.0_Ang, -0.81649_Ang, 0.51275_Ang);

    SPCE_RB->add(O_SPCE);
    SPCE_RB->add(H1_SPCE);
    SPCE_RB->add(H2_SPCE);

    std::cout << SPCE->getName() << " ";

    for (const auto& elem : SPCE->calculateCenterOfMass())
        std::cout << elem << " ";

    std::cout << '\n';
}
