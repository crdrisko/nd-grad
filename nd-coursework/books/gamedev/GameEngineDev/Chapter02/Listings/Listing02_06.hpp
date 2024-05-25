// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing02_06.hpp
// Author: crdrisko
// Date: 08/23/2023-11:51:57
// Description: Function that creates a 3x3 matrix representing a scale by factor of s along an arbitrary direction a

#ifndef LISTING02_06_HPP
#define LISTING02_06_HPP

#include "../../Matrix.hpp"
#include "../../Vector.hpp"

// clang-format off
Matrix3D MakeScale(float s, const Vector3D& a)
{
    s -= 1.0F;

    float x = a.x * s;
    float y = a.y * s;
    float z = a.z * s;

    float axay = x * a.y;
    float axaz = x * a.z;
    float ayaz = y * a.z;

    return (Matrix3D(x * a.x + 1.0F, axay, axaz,
                     axay, y * a.y + 1.0F, ayaz,
                     axaz, ayaz, z * a.z + 1.0F));
}
// clang-format on

#endif
