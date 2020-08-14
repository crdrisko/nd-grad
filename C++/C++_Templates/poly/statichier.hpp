// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
//
// Name: statichier.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/14/2020-12:04:38
// Description: Polymorphism implemented via templates

#ifndef STATICHIER_HPP
#define STATICHIER_HPP

#include "coord.hpp"

// concrete geometric object class Circle - not derived from any class
class Circle
{
public:
    void draw() const;
    Coord center_of_gravity() const;

    // ...
};

// concrete geometric object class Line - not derived from any class
class Line
{
public:
    void draw() const;
    Coord center_of_gravity() const;

    // ...
};

// ...

#endif
