// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Plane.hpp
// Author: crdrisko
// Date: 07/17/2024-07:31:46
// Description: A culmination of all listings in chapter 3 pertaining to the Plane data structure

#ifndef PLANE_HPP
#define PLANE_HPP

#include "Point.hpp"
#include "Vector.hpp"

struct Plane
{
    float x, y, z, w;

    Plane() = default;
    Plane(float nx, float ny, float nz, float d) : x {nx}, y {ny}, z {nz}, w {d} {}
    Plane(const Vector3D& n, float d) : x {n.x}, y {n.y}, z {n.z}, w {d} {}

    const Vector3D& GetNormal(void) const { return reinterpret_cast<const Vector3D&>(x); }
};

float Dot(const Plane& f, const Vector3D& v) { return (f.x * v.x + f.y * v.y + f.z * v.z); }

float Dot(const Plane& f, const Point3D& p) { return (f.x * p.x + f.y * p.y + f.z * p.z + f.w); }

#endif
