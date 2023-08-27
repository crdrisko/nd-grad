// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing01_01.hpp
// Author: crdrisko
// Date: 08/17/2023-07:37:42
// Description: Simple data structure holding the components of a 3D vector

#ifndef LISTING01_01_HPP
#define LISTING01_01_HPP

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
};

#endif
