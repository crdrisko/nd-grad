// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Transform.hpp
// Author: crdrisko
// Date: 07/16/2024-06:13:40
// Description: A culmination of all listings in chapter 2 pertaining to the Transform4D data structure

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <cmath>

#include "Vector.hpp"
#include "Matrix.hpp"
#include "Point.hpp"

// clang-format off
struct Transform4D : Matrix4D
{
    Transform4D() = default;

    Transform4D(float n00, float n01, float n02, float n03,
                float n10, float n11, float n12, float n13,
                float n20, float n21, float n22, float n23)
    {
        n[0][0] = n00; n[0][1] = n10; n[0][2] = n20; n[0][3] = 0.0f;
        n[1][0] = n01; n[1][1] = n11; n[1][2] = n21; n[1][3] = 0.0f;
        n[2][0] = n02; n[2][1] = n12; n[2][2] = n22; n[2][3] = 0.0f;
        n[3][0] = n03; n[3][1] = n13; n[3][2] = n23; n[3][3] = 1.0f;
    }

    Transform4D(const Vector3D& a, const Vector3D& b, const Vector3D& c, const Point3D& p)
    {
        n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z; n[0][3] = 0.0f;
        n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z; n[1][3] = 0.0f;
        n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z; n[2][3] = 0.0f;
        n[3][0] = p.x; n[3][1] = p.y; n[3][2] = p.z; n[3][3] = 1.0f;
    }

    Vector3D& operator[](int j) { return (*reinterpret_cast<Vector3D*>(n[j])); }
    const Vector3D& operator[](int j) const { return (*reinterpret_cast<const Vector3D*>(n[j])); }

    const Point3D& getTranslation() const { return (*reinterpret_cast<const Point3D*>(n[3])); }

    void setTranslation(const Point3D& p)
    {
        n[3][0] = p.x;
        n[3][1] = p.y;
        n[3][2] = p.z;
    }
};

Transform4D Inverse(const Transform4D& H)
{
    const Vector3D& a = H[0];
    const Vector3D& b = H[1];
    const Vector3D& c = H[2];
    const Vector3D& d = H[3];

    Vector3D s = Cross(a, b);
    Vector3D t = Cross(c, d);

    float invDet = 1.0f / Dot(s, c);

    s *= invDet;
    t *= invDet;

    Vector3D v = c * invDet;

    Vector3D r0 = Cross(b, v);
    Vector3D r1 = Cross(v, a);

    return (Transform4D(r0.x, r0.y, r0.z, -Dot(b, t),
                        r1.x, r1.y, r1.z,  Dot(a, t),
                         s.x,  s.y,  s.z, -Dot(d, s)));
}

Transform4D operator*(const Transform4D& A, const Transform4D& B)
{
    return (Transform4D(
        A(0, 0) * B(0, 0) + A(0, 1) * B(1, 0) + A(0, 2) * B(2, 0),
        A(0, 0) * B(0, 1) + A(0, 1) * B(1, 1) + A(0, 2) * B(2, 1),
        A(0, 0) * B(0, 2) + A(0, 1) * B(1, 2) + A(0, 2) * B(2, 2),
        A(0, 0) * B(0, 3) + A(0, 1) * B(1, 3) + A(0, 2) * B(2, 3) + A(0, 3),
        A(1, 0) * B(0, 0) + A(1, 1) * B(1, 0) + A(1, 2) * B(2, 0),
        A(1, 0) * B(0, 1) + A(1, 1) * B(1, 1) + A(1, 2) * B(2, 1),
        A(1, 0) * B(0, 2) + A(1, 1) * B(1, 2) + A(1, 2) * B(2, 2),
        A(1, 0) * B(0, 3) + A(1, 1) * B(1, 3) + A(1, 2) * B(2, 3) + A(1, 3),
        A(2, 0) * B(0, 0) + A(2, 1) * B(1, 0) + A(2, 2) * B(2, 0),
        A(2, 0) * B(0, 1) + A(2, 1) * B(1, 1) + A(2, 2) * B(2, 1),
        A(2, 0) * B(0, 2) + A(2, 1) * B(1, 2) + A(2, 2) * B(2, 2),
        A(2, 0) * B(0, 3) + A(2, 1) * B(1, 3) + A(2, 2) * B(2, 3) + A(2, 3)));
}

Vector3D operator*(const Transform4D& H, const Vector3D& v)
{
    return (Vector3D(H(0, 0) * v.x + H(0, 1) * v.y + H(0, 2) * v.z,
                     H(1, 0) * v.x + H(1, 1) * v.y + H(1, 2) * v.z,
                     H(2, 0) * v.x + H(2, 1) * v.y + H(2, 2) * v.z));
}

Point3D operator*(const Transform4D& H, const Point3D& p)
{
    return (Point3D(H(0, 0) * p.x + H(0, 1) * p.y + H(0, 2) * p.z + H(0, 3),
                    H(1, 0) * p.x + H(1, 1) * p.y + H(1, 2) * p.z + H(1, 3),
                    H(2, 0) * p.x + H(2, 1) * p.y + H(2, 2) * p.z + H(2, 3)));
}
// clang-format on

#endif
