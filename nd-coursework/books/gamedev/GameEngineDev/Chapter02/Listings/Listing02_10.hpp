// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing02_10.hpp
// Author: crdrisko
// Date: 06/02/2024-06:52:13
// Description: A simple data structure holding the four components of a quaternion

#ifndef LISTING02_10_HPP
#define LISTING02_10_HPP

#include "../../Matrix.hpp"
#include "../../Vector.hpp"

struct Quaternion
{
    float x, y, z, w;

    Quaternion() = default;
    Quaternion(float a, float b, float c, float s) : x {a}, y {b}, z {c}, w {s} {}
    Quaternion(const Vector3D& v, float s) : x {v.x}, y {v.y}, z {v.z}, w {s} {}

    const Vector3D& GetVectorPart() const { return (reinterpret_cast<const Vector3D&>(x)); }

    Matrix3D GetRotationMatrix();
    void SetRotationMatrix(const Matrix3D& m);
};

// clang-format off
Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
{
    return (Quaternion(
        q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
        q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
        q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
        q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z));
}
// clang-format on

#endif
