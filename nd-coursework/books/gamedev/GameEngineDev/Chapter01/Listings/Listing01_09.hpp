// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing01_09.hpp
// Author: crdrisko
// Date: 08/21/2023-08:54:15
// Description: Calculating the determinant of a 3x3 matrix

#ifndef LISTING01_09_HPP
#define LISTING01_09_HPP

#include "../../Matrix.hpp"

// clang-format off
float Determinant(const Matrix3D& M)
{
    return (M(0, 0) * (M(1, 1) * M(2, 2) - M(1, 2) * M(2, 1))
          + M(0, 1) * (M(1, 2) * M(2, 0) - M(1, 0) * M(2, 2))
          + M(0, 2) * (M(1, 0) * M(2, 1) - M(1, 1) * M(2, 0)));
}
// clang-format on

#endif