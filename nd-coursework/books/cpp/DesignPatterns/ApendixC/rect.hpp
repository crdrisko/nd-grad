// Copyright (c) 1995 by Addison-Wesley. All rights reserved.
//
// Name: rect.hpp
// Author: crdrisko
// Date: 07/23/2021-08:46:21
// Description: An axis-aligned rectangle

#ifndef RECT_HPP
#define RECT_HPP

#include "point.hpp"

class Rect
{
public:
    static const Rect Zero;

    Rect(Coord x, Coord y, Coord w, Coord h);
    Rect(const Point& origin, const Point& extent);

    Coord Width() const;
    void Width(Coord);

    Coord Height() const;
    void Height(Coord);

    Coord Left() const;
    void Left(Coord);

    Coord Bottom() const;
    void Bottom(Coord);

    Point& Origin() const;
    void Origin(const Point&);

    Point& Extent() const;
    void Extent(const Point&);

    void MoveTo(const Point&);
    void MoveBy(const Point&);

    bool IsEmpty() const;
    bool Contains(const Point&) const;
};

const Rect Rect::Zero = Rect(Point(0, 0), Point(0, 0));

#endif
