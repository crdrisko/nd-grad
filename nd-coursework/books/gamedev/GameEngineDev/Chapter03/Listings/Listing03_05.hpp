// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing03_05.hpp
// Author: crdrisko
// Date: 07/17/2024-12:14:55
// Description: Calculates a 4x4 matrix representing a reflection through a normalized plane

#ifndef LISTING03_05_HPP
#define LISTING03_05_HPP

#include "../../Plane.hpp"
#include "../../Transform.hpp"

// clang-format off
Transform4D MakeReflection(const Plane& f)
{
    float x = f.x * -2.0f;
    float y = f.y * -2.0f;
    float z = f.z * -2.0f;

    float nxny = x * f.y;
    float nxnz = x * f.z;
    float nynz = y * f.z;

    return Transform4D(x * f.x + 1.0f, nxny, nxnz, x * f.w,
                       nxny, y * f.y + 1.0f, nynz, y * f.w,
                       nxnz, nynz, z * f.z + 1.0f, z * f.w);
}
// clang-format on

#endif
