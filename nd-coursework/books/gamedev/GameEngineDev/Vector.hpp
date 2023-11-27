// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Vector.hpp
// Author: crdrisko
// Date: 08/21/2023-09:23:52
// Description: A culmination of all listings in chapter 1 pertaining to the Vector3D and Vector4D data structures

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>

struct Vector3D
{
    float x, y, z;

    Vector3D() = default;

    Vector3D(float a, float b, float c)
    {
        x = a;
        y = b;
        z = c;
    }

    float& operator[](int i) { return ((&x)[i]); }
    const float& operator[](int i) const { return ((&x)[i]); }

    Vector3D& operator*=(float s)
    {
        x *= s;
        y *= s;
        z *= s;

        return (*this);
    }

    Vector3D& operator/=(float s)
    {
        s = 1.0F / s;

        x *= s;
        y *= s;
        z *= s;

        return (*this);
    }

    Vector3D& operator+=(const Vector3D& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;

        return (*this);
    }

    Vector3D& operator-=(const Vector3D& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;

        return (*this);
    }
};

struct Vector4D
{
    float x, y, z, w;

    Vector4D() = default;

    Vector4D(float a, float b, float c, float d)
    {
        x = a;
        y = b;
        z = c;
        w = d;
    }

    float& operator[](int i) { return ((&x)[i]); }
    const float& operator[](int i) const { return ((&x)[i]); }

    Vector4D& operator*=(float s)
    {
        x *= s;
        y *= s;
        z *= s;
        w *= s;

        return (*this);
    }

    Vector4D& operator/=(float s)
    {
        s = 1.0F / s;

        x *= s;
        y *= s;
        z *= s;
        w *= s;

        return (*this);
    }

    Vector4D& operator+=(const Vector4D& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;

        return (*this);
    }

    Vector4D& operator-=(const Vector4D& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;

        return (*this);
    }
};

// Listing 1-2
inline Vector3D operator*(const Vector3D& v, float s) { return (Vector3D(v.x * s, v.y * s, v.z * s)); }

inline Vector3D operator/(const Vector3D& v, float s)
{
    s = 1.0F / s;
    return (Vector3D(v.x * s, v.y * s, v.z * s));
}

inline Vector3D operator-(const Vector3D& v) { return (Vector3D(-v.x, -v.y, -v.z)); }

inline float Magnitude(const Vector3D& v) { return (std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z)); }

inline Vector3D Normalize(const Vector3D& v) { return (v / Magnitude(v)); }

// Listing 1-3
inline Vector3D operator+(const Vector3D& a, const Vector3D& b) { return (Vector3D(a.x + b.x, a.y + b.y, a.z + b.z)); }

inline Vector3D operator-(const Vector3D& a, const Vector3D& b) { return (Vector3D(a.x - b.x, a.y - b.y, a.z - b.z)); }

#endif
