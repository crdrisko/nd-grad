// Copyright (c) 2016 by Eric Lengyel. All rights reserved.
//
// Name: Listing02_05.hpp
// Author: crdrisko
// Date: 08/23/2023-11:51:33
// Description: Function that creates a 3x3 matrix representing a scale by factors of sx, sy, and sz along the x, y, and z axes

#ifndef LISTING02_05_HPP
#define LISTING02_05_HPP

#include "../../Matrix.hpp"

Matrix3D MakeScale(float sx, float sy, float sz) { return (Matrix3D(sx, 0.0F, 0.0F, 0.0F, sy, 0.0F, 0.0F, 0.0F, sz)); }

#endif
