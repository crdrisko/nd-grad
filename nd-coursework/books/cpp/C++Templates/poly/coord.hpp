// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: coord.hpp
// Author: crdrisko
// Date: 08/14/2020-11:16:43
// Description: Missing file from book

#ifndef COORD_HPP
#define COORD_HPP

#include <cstdlib>

class Coord
{
private:
    int x, y;

public:
    Coord(int i1, int i2) : x(i1), y(i2) {}

    friend Coord operator-(Coord const& c1, Coord const& c2)
    {
        return Coord(c1.x - c2.x, c1.y - c2.y);
    }

    Coord abs() { return Coord(std::abs(x), std::abs(y)); }
};

#endif
