// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing02_03.hpp
// Author: crdrisko
// Date: 08/23/2023-09:22:53
// Description: Function that creates a 3x3 matrix representing a reflection through the plane perpendicular to an arbitrary vector a

#ifndef LISTING02_03_HPP
#define LISTING02_03_HPP

#include "../../Matrix.hpp"
#include "../../Vector.hpp"

// clang-format off
Matrix3D MakeReflection(const Vector3D& a)
{
    float x = a.x * -2.0F;
    float y = a.y * -2.0F;
    float z = a.z * -2.0F;

    float axay = x * a.y;
    float axaz = x * a.z;
    float ayaz = y * a.z;

    return (Matrix3D(x * a.x + 1.0F, axay, axaz,
                     axay, y * a.y + 1.0F, ayaz,
                     axaz, ayaz, z * a.z + 1.0F));
}
// clang-format on

#endif
