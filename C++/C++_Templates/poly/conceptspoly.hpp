// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
//
// Name: conceptspoly.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/14/2020-12:30:21
// Description: How concepts would be used with our static polymorphism example

#ifndef CONCEPTSPOLY_HPP
#define CONCEPTSPOLY_HPP

#include <vector>

#include "conceptsreq.hpp"

// draw any GeoObj
template<typename T>
requires GeoObj<T>
void myDraw(T const& obj)
{
    obj.draw();                                             // call draw() according to type of object
}

// compute distance of center of gravity between two GeoObjs
template<typename T1, typename T2>
requires GeoObj<T1> && GeoObj<T2>
Coord distance(T1 const& x1, T2 const& x2)
{
    Coord c = x1.center_of_gravity() - x2.center_of_gravity();
    return c.abs();                                         // return coordinates as absolute values
}

// draw heterogeneous collection of GeoObjs
template<typename GeoObj>
requires GeoObj<T>
void drawElems(std::vector<T> const& elems)
{
    for (std::size_t i = 0; i < elems.size(); ++i)
        elems[i].draw();                                    // call draw() according to type of element
}

#endif
