// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: variantpoly1.cpp
// Author: crdrisko
// Date: 11/11/2020-07:04:43
// Description: Programming a system of geometric objects

#include <iostream>
#include <variant>
#include <vector>

#include "circle.hpp"
#include "coord.hpp"
#include "line.hpp"
#include "rectangle.hpp"

// common type of all geometric object types:
using GeoObj = std::variant<Line, Circle, Rectangle>;

// create and initialize a collection of geometric objects:
std::vector<GeoObj> createFigure()
{
    std::vector<GeoObj> f;

    f.push_back(Line {Coord {1, 2}, Coord {3, 4}});
    f.push_back(Circle {Coord {5, 5}, 2});
    f.push_back(Rectangle {Coord {3, 3}, Coord {6, 4}});

    return f;
}

int main()
{
    std::vector<GeoObj> figure = createFigure();

    for (const GeoObj& geoobj : figure)
        std::visit([](const auto& obj) { obj.draw(); },   // polymorphic call of draw()
            geoobj);
}
