// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing01_11.hpp
// Author: crdrisko
// Date: 08/22/2023-14:19:05
// Description: Calculates the inverse of a 4x4 matrix for the Matrix4D data structure

#ifndef LISTING01_11_HPP
#define LISTING01_11_HPP

#include "../../Matrix.hpp"
#include "../../Vector.hpp"
#include "Listing01_06.hpp"
#include "Listing01_07.hpp"

// clang-format off
Matrix4D Inverse(const Matrix4D& M)
{
    const Vector3D& a = reinterpret_cast<const Vector3D&>(M[0]);
    const Vector3D& b = reinterpret_cast<const Vector3D&>(M[1]);
    const Vector3D& c = reinterpret_cast<const Vector3D&>(M[2]);
    const Vector3D& d = reinterpret_cast<const Vector3D&>(M[3]);

    const float& x = M(3, 0);
    const float& y = M(3, 1);
    const float& z = M(3, 2);
    const float& w = M(3, 3);

    Vector3D s = Cross(a, b);
    Vector3D t = Cross(c, d);
    Vector3D u = a * y - b * x;
    Vector3D v = c * w - d * z;

    float invDet = 1.0F / (Dot(s, v) + Dot(t, u));

    s *= invDet;
    t *= invDet;
    u *= invDet;
    v *= invDet;

    Vector3D r0 = Cross(b, v) + t * y;
    Vector3D r1 = Cross(v, a) - t * x;
    Vector3D r2 = Cross(d, u) + s * w;
    Vector3D r3 = Cross(u, c) - s * z;

    return (Matrix4D(r0.x, r0.y, r0.z, -Dot(b, t),
                     r1.x, r1.y, r1.z,  Dot(a, t),
                     r2.x, r2.y, r2.z, -Dot(d, s),
                     r3.x, r3.y, r3.z,  Dot(c, s)));
}
// clang-format on

#endif
