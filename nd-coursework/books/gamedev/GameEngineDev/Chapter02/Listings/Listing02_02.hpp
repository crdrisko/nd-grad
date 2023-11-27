// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing02_02.hpp
// Author: crdrisko
// Date: 08/23/2023-09:10:10
// Description: Function that creates a 3x3 matrix representing rotations through the angle t about an arbitraty axis a

#ifndef LISTING02_02_HPP
#define LISTING02_02_HPP

#include <cmath>

#include "../../Matrix.hpp"
#include "../../Vector.hpp"

// clang-format off
Matrix3D MakeRotation(float t, const Vector3D& a)
{
    float c = std::cos(t);
    float s = std::sin(t);
    float d = 1.0F - c;

    float x = a.x * d;
    float y = a.y * d;
    float z = a.z * d;

    float axay = x * a.y;
    float axaz = x * a.z;
    float ayaz = y * a.z;

    return (Matrix3D(c + x * a.x, axay - s * a.z, axaz + s * a.y,
                     axay + s * a.z, c + y * a.y, ayaz - s * a.x,
                     axaz - s * a.y, ayaz + s * a.x, c + z * a.z));
}
// clang-format on


#endif
