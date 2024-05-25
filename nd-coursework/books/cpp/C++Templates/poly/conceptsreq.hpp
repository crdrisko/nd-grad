// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: conceptsreq.hpp
// Author: crdrisko
// Date: 08/14/2020-12:27:08
// Description: Demonstrating how concepts can help choose template parameters that satisfy specific constraints

#ifndef CONCEPTSREQ_HPP
#define CONCEPTSREQ_HPP

#include "coord.hpp"

template<typename T>
concept GeoObj = requires(T x) {
    {
        x.draw()
    } -> void;
    {
        x.center_of_gravity()
    } -> Coord;

    // ...
};

#endif
