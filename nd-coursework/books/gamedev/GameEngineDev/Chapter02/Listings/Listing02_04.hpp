// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing02_04.hpp
// Author: crdrisko
// Date: 08/23/2023-11:30:00
// Description: Function that creates a 3x3 matrix representing an involution through an arbitrary vector a

#ifndef LISTING02_04_HPP
#define LISTING02_04_HPP

#include "../../Matrix.hpp"
#include "../../Vector.hpp"

// clang-format off
Matrix3D MakeInvolution(const Vector3D& a)
{
    float x = a.x * 2.0F;
    float y = a.y * 2.0F;
    float z = a.z * 2.0F;

    float axay = x * a.y;
    float axaz = x * a.z;
    float ayaz = y * a.z;

    return (Matrix3D(x * a.x - 1.0F, axay, axaz,
                     axay, y * a.y - 1.0F, ayaz,
                     axaz, ayaz, z * a.z - 1.0F));
}
// clang-format on

#endif
