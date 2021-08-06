// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: polygon.cpp
// Author: crdrisko
// Date: 08/06/2021-06:57:20
// Description: Demonstrating how move semantics works for a derived class that doesn't override the destructor

#include "polygon.hpp"

#include "geoobj.hpp"

int main()
{
    Polygon p0 {"Poly1", {Coord {1, 1}, Coord {1, 9}, Coord {9, 9}, Coord {9, 1}}};
    Polygon p1 {p0};              // copy
    Polygon p2 {std::move(p0)};   // move

    p0.draw();
    p1.draw();
    p2.draw();
}
