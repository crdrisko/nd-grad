// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing02_13.hpp
// Author: crdrisko
// Date: 06/03/2024-16:10:03
// Description: Set the members of the Quaternion data structure for which it's called to the values
//                  corresponding to a quaternion equivalent to the 3x3 rotation matrix m

#ifndef LISTING02_13_HPP
#define LISTING02_13_HPP

#include <cmath>

#include "../../Matrix.hpp"
#include "Listing02_10.hpp"

// clang-format off
void Quaternion::SetRotationMatrix(const Matrix3D& m)
{
    float m00 = m(0, 0);
    float m11 = m(1, 1);
    float m22 = m(2, 2);

    float sum = m00 + m11 + m22;

    if (sum > 0.0f)
    {
        w = std::sqrt(sum + 1.0f) * 0.5f;
        float f = 0.25f / w;

        x = (m(2, 1) - m(1, 2)) * f;
        y = (m(0, 2) - m(2, 0)) * f;
        z = (m(1, 0) - m(0, 1)) * f;
    }
    else if (m00 > m11 && m00 > m22)
    {
        x = std::sqrt(m00 - m11 - m22 + 1.0f) * 0.5f;
        float f = 0.25f / x;

        y = (m(1, 0) + m(0, 1)) * f;
        z = (m(0, 2) + m(2, 0)) * f;
        w = (m(2, 1) - m(1, 2)) * f;
    }
    else if (m11 > m22)
    {
        y = std::sqrt(m11 - m00 - m22 + 1.0f) * 0.5f;
        float f = 0.25f / y;

        x = (m(1, 0) + m(0, 1)) * f;
        z = (m(2, 1) + m(1, 2)) * f;
        w = (m(0, 2) - m(2, 0)) * f;
    }
    else
    {
        z = std::sqrt(m22 - m00 - m11 + 1.0f) * 0.5f;
        float f = 0.25f / z;

        x = (m(0, 2) + m(2, 0)) * f;
        y = (m(2, 1) + m(1, 2)) * f;
        w = (m(1, 0) - m(0, 1)) * f;
    }
}
// clang-format on

#endif
