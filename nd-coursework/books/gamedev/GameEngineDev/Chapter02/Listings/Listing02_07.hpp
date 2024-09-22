// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing02_07.hpp
// Author: crdrisko
// Date: 06/02/2024-05:58:41
// Description: Function that creates a 3x3 matrix representing a skew by the angle t along the 
//                  direction a based on the projected length aling the direction b

#ifndef LISTING02_07_HPP
#define LISTING02_07_HPP

#include <cmath>

#include "../../Matrix.hpp"
#include "../../Vector.hpp"

// clang-format off
Matrix3D MakeSkew(float t, const Vector3D& a, const Vector3D& b)
{
    t = std::tan(t);

    float x = a.x * t;
    float y = a.y * t;
    float z = a.z * t;

    return (Matrix3D(x * b.x + 1.0f, x * b.y, x * b.z,
                     y * b.x, y * b.y + 1.0f, y * b.z,
                     z * b.x, z * b.y, z * b.z + 1.0f));
}
// clang-format on

#endif
