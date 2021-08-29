// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: rigidBody.hpp
// Author: crdrisko
// Date: 07/28/2021-07:23:50
// Description:

#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include "molecularEntity.hpp"

class RigidBody : public CompositeMolecularEntity
{
public:
    explicit RigidBody(const std::string& name_) : CompositeMolecularEntity {name_} {}
};

#endif
