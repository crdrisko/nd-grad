// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing03_02.hpp
// Author: crdrisko
// Date: 07/17/2024-07:05:39
// Description: Calculate the distance between a point and a line

#ifndef LISTING03_02_HPP
#define LISTING03_02_HPP

#include <cmath>

#include "../../Point.hpp"
#include "../../Vector.hpp"

float DistPointLine(const Point3D& q, const Point3D& p, const Vector3D& v)
{
    Vector3D a = Cross(q - p, v);
    return (std::sqrt(Dot(a, a) / Dot(v, v)));
}

#endif
