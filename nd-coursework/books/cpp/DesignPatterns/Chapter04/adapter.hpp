// Copyright (c) 1995 by Addison-Wesley. All rights reserved.
//
// Name: adapter.hpp
// Author: crdrisko
// Date: 07/23/2021-08:26:19
// Description: Convert the interface of a class into another interface clients expect

#ifndef ADAPTER_HPP
#define ADAPTER_HPP

#include "../ApendixC/Point.hpp"

class TextShape;

class Manipulator
{
};

class TextManipulator : public Manipulator
{
public:
    TextManipulator(const TextShape*) : Manipulator() {}
};

// Target - defines the domain-specific interface that Client uses
class Shape
{
public:
    Shape();

    virtual void BoundingBox(Point& bottomLeft, Point& topRight) const;
    virtual Manipulator* CreateManipulator() const;
};

// Adaptee - defines an existing interface that needs adapting
class TextView
{
public:
    TextView();

    void GetOrigin(Coord& x, Coord& y) const;
    void GetExtent(Coord& width, Coord& height) const;

    virtual bool IsEmpty() const;
};

// Adapter - adapts the interface of Adaptee to the Target interface
class TextShape : public Shape, private TextView
{
public:
    TextShape();

    virtual void BoundingBox(Point& bottomLeft, Point& topRight) const;
    virtual bool IsEmpty() const;
    virtual Manipulator* CreateManipulator() const;
};

// Client - collaborates with objects conforming to the Target interface
class DrawingEditor;

#endif
