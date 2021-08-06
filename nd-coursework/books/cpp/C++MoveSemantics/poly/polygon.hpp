// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: polygon.hpp
// Author: crdrisko
// Date: 08/06/2021-06:57:10
// Description: A polymorphic derived class without the special member functions

#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>

#include "geoobj.hpp"

class Polygon : public GeoObj
{
private:
    std::vector<Coord> points;

public:
    // constructor for name and list of Coords:
    Polygon(std::string n, std::initializer_list<Coord> pl = {}) : GeoObj {std::move(n)}, points {std::move(pl)} {}

    virtual void draw() const override
    {
        std::cout << "polygon '" << name << "' over";

        for (auto& p : points)
            std::cout << " " << p;

        std::cout << '\n';
    }
};

#endif
