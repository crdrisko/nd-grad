// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: dynahier.hpp
// Author: crdrisko
// Date: 08/14/2020-11:34:54
// Description: Polymorphism implemented via inheritance

#ifndef DYNAHIER_HPP
#define DYNAHIER_HPP

#include "coord.hpp"

// common abstract base class GeoObj for geometric objects
class GeoObj
{
public:
    virtual ~GeoObj() = default;

    // draw geometric object:
    virtual void draw() const = 0;

    // return center of gravity of geometric object:
    virtual Coord center_of_gravity() const = 0;

    // ...
};

// concrete geometric object class Circle - derived from GeoObj
class Circle : public GeoObj
{
public:
    virtual void draw() const override;
    virtual Coord center_of_gravity() const override;

    // ...
};

// concrete geometric object class Line - derived from GeoObj
class Line : public GeoObj
{
public:
    virtual void draw() const override;
    virtual Coord center_of_gravity() const override;

    // ...
};

// ...

#endif
