// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: line.hpp
// Author: crdrisko
// Date: 11/11/2020-07:21:52
// Description: A geometric representation of a line

#ifndef LINE_HPP
#define LINE_HPP

#include <iostream>

#include "coord.hpp"

class Line
{
private:
    Coord from;
    Coord to;

public:
    Line(Coord f, Coord t) : from {f}, to {t} {}

    void move(const Coord& c)
    {
        from += c;
        to += c;
    }

    void draw() const { std::cout << "line from " << from << " to " << to << '\n'; }
};

#endif
