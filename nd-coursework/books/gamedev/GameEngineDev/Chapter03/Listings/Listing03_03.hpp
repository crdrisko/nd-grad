// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing03_03.hpp
// Author: crdrisko
// Date: 07/17/2024-07:08:04
// Description: Calculate the distance between two lines

#ifndef LISTING03_03_HPP
#define LISTING03_03_HPP

#include <cmath>
#include <limits>

#include "../../Point.hpp"
#include "../../Vector.hpp"

float DistLineLine(const Point3D& p1, const Vector3D& v1, const Point3D& p2, const Vector3D& v2)
{
    Vector3D dp = p2 - p1;

    float v11 = Dot(v1, v1);
    float v22 = Dot(v2, v2);
    float v12 = Dot(v1, v2);

    float det = v12 * v12 - v11 * v22;

    if (std::fabs(det) > std::numeric_limits<float>::min())
    {
        det = 1.0f / det;

        float dpv1 = Dot(dp, v1);
        float dpv2 = Dot(dp, v2);
        float t1   = (v12 * dpv2 - v22 * dpv1) * det;
        float t2   = (v11 * dpv2 - v12 * dpv1) * det;

        return Magnitude(dp + v2 * t2 - v1 * t1);
    }

    // The lines are nearly parallel
    Vector3D a = Cross(dp, v1);

    return std::sqrt(Dot(a, a) / v11);
}

#endif
