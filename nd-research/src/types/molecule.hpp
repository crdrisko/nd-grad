// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: molecule.hpp
// Author: crdrisko
// Date: 07/28/2021-07:23:41
// Description:

#ifndef MOLECULE_HPP
#define MOLECULE_HPP

#include "molecularEntity.hpp"

class Molecule : public CompositeMolecularEntity
{
public:
    explicit Molecule(const std::string& name_) : CompositeMolecularEntity {name_} {}
};

#endif
