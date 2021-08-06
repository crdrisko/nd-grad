// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: geoobj.hpp
// Author: crdrisko
// Date: 08/06/2021-06:57:00
// Description: A polymorphic base class with move semantics (and members)

#ifndef GEOOBJ_HPP
#define GEOOBJ_HPP

#include <string>

#include "coord.hpp"

class GeoObj
{
protected:
    std::string name;   // name of the geometric object

    GeoObj(std::string n) : name {std::move(n)} {}

public:
    std::string getName() const { return name; }

    virtual void draw() const = 0;         // pure virtual function (introducing the API)
    virtual ~GeoObj()         = default;   // would disable move semantics for name

protected:
    // enable copy and move semantics (callable only for derived classes):
    GeoObj(const GeoObj&) = default;
    GeoObj(GeoObj&&)      = default;

    // disable assignment operator (due to the problem of slicing):
    GeoObj& operator=(GeoObj&&) = delete;
    GeoObj& operator=(const GeoObj&) = delete;

    // ...
};

#endif
