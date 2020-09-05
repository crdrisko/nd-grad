// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: min.cpp - Version 1.0.0
// Author: crdrisko
// Date: 09/04/2020-07:55:07
// Description: Using the instantiation-safe min() function on various types

#include "min1.hpp"

struct X1 {};
bool operator<(X1 const&, X1 const&) { return true; }

struct X2 {};
bool operator<(X2, X2) { return true; }

struct X3 {};
bool operator<(X3&, X3&) { return true; }

struct X4 {};

struct BoolConvertible
{
    operator bool() const { return true; }                  // implicit conversion to bool
};

struct X5 {};
BoolConvertible operator<(X5 const&, X5 const&) { return BoolConvertible(); }

struct NotBoolConvertible {};                               // no conversion to bool

struct X6 {};
NotBoolConvertible operator<(X6 const&, X6 const&) { return NotBoolConvertible(); }

struct BoolLike
{
    explicit operator bool() const {return true; }          // explicit conversion to bool
};

struct X7 {};
BoolLike operator<(X7 const&, X7 const&) { return BoolLike(); }

int main()
{
    min(X1(), X1());                                        // X1 can be passed to min()
    min(X2(), X2());                                        // X2 can be passed to min()
    min(X3(), X3());                                        // ERROR: X3 cannot be passed to min()
    min(X4(), X4());                                        // ERROR: X4 cannot be passed to min()
    min(X5(), X5());                                        // X5 can be passed to min()
    min(X6(), X6());                                        // ERROR: X6 cannot be passed to min()
    min(X7(), X7());                                        // UNEXPECTED ERROR: X7 cannot be passed to min()
}
