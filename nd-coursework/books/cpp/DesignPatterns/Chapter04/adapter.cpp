// Copyright (c) 1995 by Addison-Wesley. All rights reserved.
//
// Name: adapter.cpp
// Author: crdrisko
// Date: 07/22/2021-15:43:53
// Description: Convert the interface of a class into another interface clients expect

#include "adapter.hpp"

#include "../ApendixC/Point.hpp"

void TextShape::BoundingBox(Point& bottomLeft, Point& topRight) const
{
    Coord bottom, left, width, height;

    GetOrigin(bottom, left);
    GetExtent(width, height);

    bottomLeft = Point(bottom, left);
    topRight   = Point(bottom + height, left + width);
}

bool TextShape::IsEmpty() const { return TextView::IsEmpty(); }

Manipulator* TextShape::CreateManipulator() const { return new TextManipulator(this); }
