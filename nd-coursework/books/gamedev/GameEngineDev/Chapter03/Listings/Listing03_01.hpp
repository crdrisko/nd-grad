// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing03_01.hpp
// Author: crdrisko
// Date: 07/16/2024-06:11:37
// Description: Multiplication operator for a normal vector represented by a Vector3D and a
//                  transform matrix represented by a Transform4D

#ifndef LISTING03_01_HPP
#define LISTING03_01_HPP

#include "../../Transform.hpp"
#include "../../Vector.hpp"

// clang-format off
Vector3D operator*(const Vector3D& n, const Transform4D& H)
{
    return (Vector3D(n.x * H(0, 0) + n.y * H(1, 0) + n.z * H(2, 0),
                     n.x * H(0, 1) + n.y * H(1, 1) + n.z * H(2, 1),
                     n.x * H(0, 2) + n.y * H(1, 2) + n.z * H(2, 2)));
}
// clang-format on

#endif
