// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: issame.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/28/2020-21:38:42
// Description: Using IsSameT to choose implementations based of template parameter type

#include <iostream>

#include "issame.hpp"

template<typename T>
void fooImpl(T, TrueType)
{
    std::cout << "fooImpl(T, true) for int called\n";
}

template<typename T>
void fooImpl(T, FalseType)
{
    std::cout << "fooImpl(T, false) for other type called\n";
}

template<typename T>
void foo(T t)
{
    fooImpl(t, IsSameT<T, int>{});                          // choose impl. depending on whether T is int
}

int main()
{
    foo(42);                                                // calls fooImpl(42, TrueType)
    foo(7.7);                                               // calls fooImpl(7.7, FalseType)
}
