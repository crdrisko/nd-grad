// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Matrix.hpp
// Author: crdrisko
// Date: 08/22/2023-09:06:43
// Description: A culmination of all listings in chapter 1 pertaining to the Matrix3D and Matrix4D data structures

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cmath>

#include "Vector.hpp"

// clang-format off
struct Matrix3D
{
private:
    float n[3][3];

public:
    Matrix3D() = default;

    Matrix3D(float n00, float n01, float n02, float n10, float n11, float n12, float n20, float n21, float n22)
    {
        n[0][0] = n00; n[0][1] = n10; n[0][2] = n20;
        n[1][0] = n01; n[1][1] = n11; n[1][2] = n21;
        n[2][0] = n02; n[2][1] = n12; n[2][2] = n22;
    }

    Matrix3D(const Vector3D& a, const Vector3D& b, const Vector3D& c)
    {
        n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
        n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
        n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
    }

    float& operator()(int i, int j) { return (n[j][i]); }
    const float& operator()(int i, int j) const { return (n[j][i]); }

    Vector3D& operator[](int j) { return (*reinterpret_cast<Vector3D*>(n[j])); }
    const Vector3D& operator[](int j) const { return (*reinterpret_cast<const Vector3D*>(n[j])); }
};

struct Matrix4D
{
private:
    float n[4][4];

public:
    Matrix4D() = default;

    Matrix4D(float n00, float n01, float n02, float n03,
             float n10, float n11, float n12, float n13,
             float n20, float n21, float n22, float n23,
             float n30, float n31, float n32, float n33)
    {
        n[0][0] = n00; n[0][1] = n10; n[0][2] = n20; n[0][3] = n30;
        n[1][0] = n01; n[1][1] = n11; n[1][2] = n21; n[1][3] = n31;
        n[2][0] = n02; n[2][1] = n12; n[2][2] = n22; n[2][3] = n32;
        n[3][0] = n03; n[3][1] = n13; n[3][2] = n23; n[3][3] = n33;
    }

    Matrix4D(const Vector4D& a, const Vector4D& b, const Vector4D& c, const Vector4D& d)
    {
        n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z; n[0][3] = a.w;
        n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z; n[1][3] = b.w;
        n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z; n[2][3] = c.w;
        n[3][0] = d.x; n[3][1] = d.y; n[3][2] = d.z; n[3][3] = d.w;
    }

    float& operator()(int i, int j) { return (n[j][i]); }
    const float& operator()(int i, int j) const { return (n[j][i]); }

    Vector4D& operator[](int j) { return (*reinterpret_cast<Vector4D*>(n[j])); }
    const Vector4D& operator[](int j) const { return (*reinterpret_cast<const Vector4D*>(n[j])); }
};

// Listing 1-5
Matrix3D operator*(const Matrix3D& A, const Matrix3D& B)
{
    return (Matrix3D( A(0, 0) * B(0, 0) + A(0, 1) * B(1, 0) + A(0, 2) * B(2, 0),
                      A(0, 0) * B(0, 1) + A(0, 1) * B(1, 1) + A(0, 2) * B(2, 1),
                      A(0, 0) * B(0, 2) + A(0, 1) * B(1, 2) + A(0, 2) * B(2, 2),
                      A(1, 0) * B(0, 0) + A(1, 1) * B(1, 0) + A(1, 2) * B(2, 0),
                      A(1, 0) * B(0, 1) + A(1, 1) * B(1, 1) + A(1, 2) * B(2, 1),
                      A(1, 0) * B(0, 2) + A(1, 1) * B(1, 2) + A(1, 2) * B(2, 2),
                      A(2, 0) * B(0, 0) + A(2, 1) * B(1, 0) + A(2, 2) * B(2, 0),
                      A(2, 0) * B(0, 1) + A(2, 1) * B(1, 1) + A(2, 2) * B(2, 1),
                      A(2, 0) * B(0, 2) + A(2, 1) * B(1, 2) + A(2, 2) * B(2, 2) ));
}

Vector3D operator*(const Matrix3D& M, const Vector3D& v)
{
    return (Vector3D(M(0, 0) * v.x + M(0, 1) * v.y + M(0, 2) * v.z,
                     M(1, 0) * v.x + M(1, 1) * v.y + M(1, 2) * v.z,
                     M(2, 0) * v.x + M(2, 1) * v.y + M(2, 2) * v.z));
}
// clang-format on

#endif
