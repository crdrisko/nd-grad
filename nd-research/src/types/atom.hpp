// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: atom.hpp
// Author: crdrisko
// Date: 07/28/2021-07:23:36
// Description:

#ifndef ATOM_HPP
#define ATOM_HPP

#include "molecularEntity.hpp"

using namespace CppUnits::Literals;

static inline std::unordered_map<std::string, CppUnits::Mass> AtomicMasses {{"H", (1.0079_amu * 1.0_mol)},
    {"O", (15.9994_amu * 1.0_mol)}};

class Atom final : public MolecularEntity
{
private:
    PositionVector positions;

public:
    explicit Atom(const std::string& name_, CppUnits::Length x_, CppUnits::Length y_, CppUnits::Length z_)
        : MolecularEntity {name_}, positions {x_, y_, z_}
    {
    }

    // Public functions...
    CppUnits::Mass getMass() const override { return AtomicMasses[this->getName()]; }
    PositionVector calculateCenterOfMass() override { return positions; }
};

#endif
