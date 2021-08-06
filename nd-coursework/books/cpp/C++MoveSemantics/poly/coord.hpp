// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: coord.hpp
// Author: crdrisko
// Date: 08/06/2021-06:58:02
// Description: A simple 2D-cartesian coordinate

#ifndef COORD_HPP
#define COORD_HPP

#include <iostream>

class Coord
{
private:
    int x {0};   // x coordinate
    int y {0};   // y coordinate

public:
    // default constructor:
    Coord() = default;

    // other constructor:
    Coord(int xarg, int yarg) : x {xarg}, y {yarg} {}

    friend Coord operator+(Coord c1, Coord c2) { return Coord {c1.x + c2.x, c1.y + c2.y}; }   // add
    friend Coord operator-(Coord c1, Coord c2) { return Coord {c1.x - c2.x, c1.y - c2.y}; }   // diff
    Coord operator-() const { return Coord {-x, -y}; }                                        // negate
    void operator+=(Coord c) { *this = *this + c; }                                           // +=
    void operator-=(Coord c) { operator+=(-c); /* or as above */ }                            // -=

    int getX() const { return x; }
    int getY() const { return y; }

    friend std::ostream& operator<<(std::ostream& strm, Coord c) { return strm << '(' << c.x << ',' << c.y << ')'; }
};

#endif
