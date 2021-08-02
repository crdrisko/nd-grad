// Copyright (c) 1995 by Addison-Wesley. All rights reserved.
//
// Name: point.hpp
// Author: crdrisko
// Date: 07/23/2021-08:24:53
// Description: A point in two-dimensional Cartesian coordinate space

#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

using Coord = float;

class Point
{
public:
    static const Point Zero;

    Point(Coord x = 0.0, Coord y = 0.0);

    Coord X() const;
    void X(Coord x);
    Coord Y() const;
    void Y(Coord y);

    friend Point operator+(const Point&, const Point&);
    friend Point operator-(const Point&, const Point&);
    friend Point operator*(const Point&, const Point&);
    friend Point operator/(const Point&, const Point&);

    Point& operator+=(const Point&);
    Point& operator-=(const Point&);
    Point& operator*=(const Point&);
    Point& operator/=(const Point&);

    Point operator-();

    friend bool operator==(const Point&, const Point&);
    friend bool operator!=(const Point&, const Point&);

    friend std::ostream& operator<<(std::ostream&, const Point&);
    friend std::istream& operator>>(std::istream&, Point&);
};

#endif
