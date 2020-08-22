// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: dynapoly.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/14/2020-11:35:03
// Description: Demonstration of using dynamic polymorphism

#include <vector>

#include "coord.hpp"
#include "dynahier.hpp"

// draw any GeoObj
void myDraw(GeoObj const& obj)
{
    obj.draw();                                             // call draw() according to type of object
}

// compute distance of center of gravity between two GeoObjs
Coord distance(GeoObj const& x1, GeoObj const& x2)
{
    Coord c = x1.center_of_gravity() - x2.center_of_gravity();
    return c.abs();                                         // return coordinates as absolute values
}

// draw heterogeneous collection of GeoObjs
void drawElems(std::vector<GeoObj*> const& elems)
{
    for (std::size_t i = 0; i < elems.size(); ++i)
        elems[i]->draw();                                   // call draw() according to type of element
}

int main()
{
    Line l;
    Circle c, c1, c2;

    myDraw(l);                                              // myDraw(GeoObj&) => Line::draw()
    myDraw(c);                                              // myDraw(GeoObj&) => Circle::draw()

    distance(c1, c2);                                       // distance(GeoObj&, GeoObj&)
    distance(l, c);                                         // distance(GeoObj&, GeoObj&)

    std::vector<GeoObj*> coll;                              // heterogeneous collection
    coll.push_back(&l);                                     // insert line
    coll.push_back(&c);                                     // insert circle
    drawElems(coll);                                        // draw different kinds of GeoObjs
}
