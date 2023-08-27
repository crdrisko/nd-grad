// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing01_06.hpp
// Author: crdrisko
// Date: 08/19/2023-08:40:32
// Description: The dot product between two Vector3D structures

#ifndef LISTING01_06_HPP
#define LISTING01_06_HPP

#include "../../Vector.hpp"

inline float Dot(const Vector3D& a, const Vector3D& b) { return (a.x * b.x + a.y * b.y + a.z * b.z); }

#endif
