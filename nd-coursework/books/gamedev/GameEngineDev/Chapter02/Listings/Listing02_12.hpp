// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing02_12.hpp
// Author: crdrisko
// Date: 06/03/2024-16:09:53
// Description: Create a 3x3 matrix that corresponds to the Quaternion data structure for which it's called

#ifndef LISTING02_12_HPP
#define LISTING02_12_HPP

#include "../../Matrix.hpp"
#include "Listing02_10.hpp"

// clang-format off
Matrix3D Quaternion::GetRotationMatrix()
{
    float x2 = x * x;
    float y2 = y * y;
    float z2 = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;

    return (Matrix3D(1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy),
                     2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx),
                     2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2)));
}
// clang-format on

#endif
