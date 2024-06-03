// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing02_11.hpp
// Author: crdrisko
// Date: 06/02/2024-07:09:31
// Description: Code to rotate a vector v using the quaternion q

#ifndef LISTING02_11_HPP
#define LISTING02_11_HPP

#include "../../Chapter01/Listings/Listing01_06.hpp"
#include "../../Chapter01/Listings/Listing01_07.hpp"
#include "../../Vector.hpp"
#include "Listing02_10.hpp"

Vector3D Transform(const Vector3D& v, const Quaternion& q)
{
    const Vector3D& b = q.GetVectorPart();
    float b2          = b.x * b.x + b.y * b.y + b.z * b.z;

    return (v * (q.w * q.w - b2) + b * (Dot(v, b) * 2.0f) + Cross(b, v) * (q.w * 2.0f));
}

#endif
