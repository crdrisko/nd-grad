// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing01_10.hpp
// Author: crdrisko
// Date: 08/22/2023-14:19:01
// Description: Calculates the inverse of a 3x3 matrix for the Matrix3D data structure

#ifndef LISTING01_10_HPP
#define LISTING01_10_HPP

#include "../../Matrix.hpp"
#include "Listing01_06.hpp"
#include "Listing01_07.hpp"

// clang-format off
Matrix3D Inverse(const Matrix3D& M)
{
    const Vector3D& a = M[0];
    const Vector3D& b = M[1];
    const Vector3D& c = M[2];

    Vector3D r0 = Cross(b, c);
    Vector3D r1 = Cross(c, a);
    Vector3D r2 = Cross(a, b);

    float invDet = 1.0F / Dot(r2, c);

   
    return (Matrix3D(r0.x * invDet, r0.y * invDet, r0.z * invDet,
                     r1.x * invDet, r1.y * invDet, r1.z * invDet,
                     r2.x * invDet, r2.y * invDet, r2.z * invDet));
}
// clang-format on

#endif
