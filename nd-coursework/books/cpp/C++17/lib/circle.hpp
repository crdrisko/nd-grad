// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: circle.hpp
// Author: crdrisko
// Date: 11/11/2020-07:05:00
// Description: A geometric representation of a circle

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <iostream>

#include "coord.hpp"

class Circle
{
private:
    Coord center;
    int rad;

public:
    Circle(Coord c, int r) : center {c}, rad {r} {}

    void move(const Coord& c) { center += c; }

    void draw() const { std::cout << "circle at " << center << " with radius " << rad << '\n'; }
};

#endif
