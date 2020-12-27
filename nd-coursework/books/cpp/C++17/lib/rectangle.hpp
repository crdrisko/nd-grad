// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: rectangle.hpp
// Author: crdrisko
// Date: 11/11/2020-07:22:38
// Description: A geometric representation of a rectangle

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <iostream>

#include "coord.hpp"

class Rectangle
{
private:
    Coord from;
    Coord to;

public:
    Rectangle(Coord f, Coord t) : from {f}, to {t} {}

    void move(const Coord& c)
    {
        from += c;
        to += c;
    }

    void draw() const { std::cout << "rectangle from " << from << " to " << to << '\n'; }
};

#endif
