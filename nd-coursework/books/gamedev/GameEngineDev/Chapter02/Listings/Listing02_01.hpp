// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing02_01.hpp
// Author: crdrisko
// Date: 08/23/2023-08:47:13
// Description: Functions that create 3x3 matricies representing rotations through the angle t about the x, y, and z axes

#ifndef LISTING02_01_HPP
#define LISTING02_01_HPP

#include <cmath>

#include "../../Matrix.hpp"

// clang-format off
Matrix3D MakeRotationX(float t)
{
    float c = std::cos(t);
    float s = std::sin(t);

    return (Matrix3D(1.0F, 0.0F, 0.0F, 
                     0.0F,  c,   -s, 
                     0.0F,  s,    c  ));
}

Matrix3D MakeRotationY(float t)
{
    float c = std::cos(t);
    float s = std::sin(t);

    return (Matrix3D( c,   0.0F,  s, 
                     0.0F, 1.0F, 0.0F, 
                     -s,   0.0F,  c  ));
}

Matrix3D MakeRotationZ(float t)
{
    float c = std::cos(t);
    float s = std::sin(t);

    return (Matrix3D( c,   -s,   0.0F, 
                      s,    c,   0.0F, 
                     0.0F, 0.0F, 1.0F));
}
// clang-format on

#endif
