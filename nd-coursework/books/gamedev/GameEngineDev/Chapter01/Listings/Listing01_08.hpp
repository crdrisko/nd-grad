// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing01_08.hpp
// Author: crdrisko
// Date: 08/20/2023-08:39:15
// Description: Projection and rejection added to the Vector3D data structure

#ifndef LISTING01_08_HPP
#define LISTING01_08_HPP

#include "../../Vector.hpp"
#include "Listing01_06.hpp"

inline Vector3D Project(const Vector3D& a, const Vector3D& b) { return (b * (Dot(a, b) / Dot(b, b))); }

inline Vector3D Reject(const Vector3D& a, const Vector3D& b) { return (a - b * (Dot(a, b) / Dot(b, b))); }

#endif
