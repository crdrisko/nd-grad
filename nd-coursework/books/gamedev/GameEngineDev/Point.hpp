// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Point.hpp
// Author: crdrisko
// Date: 06/02/2024-06:21:09
// Description: A culmination of all listings in chapter 2 pertaining to the Point3D data structure

#ifndef POINT_HPP
#define POINT_HPP

#include "Vector.hpp"

struct Point3D : Vector3D
{
    Point3D() = default;
    Point3D(float a, float b, float c) : Vector3D(a, b, c) {}
};

inline Point3D operator+(const Point3D& a, const Vector3D& b) { return (Point3D(a.x + b.x, a.y + b.y, a.z + b.z)); }

inline Vector3D operator-(const Point3D& a, const Point3D& b) { return (Vector3D(a.x - b.x, a.y - b.y, a.z - b.z)); }

#endif
