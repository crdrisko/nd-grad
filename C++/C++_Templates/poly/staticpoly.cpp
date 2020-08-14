// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
//
// Name: staticpoly.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/14/2020-12:09:22
// Description: Demonstration of using static polymorphism

#include <vector>

#include "coord.hpp"
#include "statichier.hpp"

// draw any GeoObj
template<typename GeoObj>
void myDraw(GeoObj const& obj)
{
    obj.draw();                                             // call draw() according to type of object
}

// compute distance of center of gravity between two GeoObjs
template<typename GeoObj1, typename GeoObj2>
Coord distance(GeoObj1 const& x1, GeoObj2 const& x2)
{
    Coord c = x1.center_of_gravity() - x2.center_of_gravity();
    return c.abs();                                         // return coordinates as absolute values
}

// draw heterogeneous collection of GeoObjs
template<typename GeoObj>
void drawElems(std::vector<GeoObj> const& elems)
{
    for (std::size_t i = 0; i < elems.size(); ++i)
        elems[i].draw();                                    // call draw() according to type of element
}

int main()
{
    Line l;
    Circle c, c1, c2;

    myDraw(l);                                              // myDraw<Line>(GeoObj&) => Line::draw()
    myDraw(c);                                              // myDraw<Circle>(GeoObj&) => Circle::draw()

    distance(c1, c2);                                       // distance<Circle, Circle>(GeoObj1&, GeoObj2&)
    distance(l, c);                                         // distance<Line, Circle>(GeoObj1&, GeoObj2&)

    // std::vector<GeoObj*> coll;                           // ERROR: no heterogeneous collection possible
    std::vector<Line> coll;                                 // OK: homogeneous collection possible
    coll.push_back(l);                                      // insert line
    drawElems(coll);                                        // draw all lines
}
