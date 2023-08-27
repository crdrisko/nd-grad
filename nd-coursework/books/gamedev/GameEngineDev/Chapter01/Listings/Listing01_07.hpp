// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing01_07.hpp
// Author: crdrisko
// Date: 08/19/2023-08:45:52
// Description: The cross product between two Vector3D structures

#ifndef LISTING01_07_HPP
#define LISTING01_07_HPP

#include "../../Vector.hpp"

inline Vector3D Cross(const Vector3D& a, const Vector3D& b)
{
    return (Vector3D(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x));
}

#endif
