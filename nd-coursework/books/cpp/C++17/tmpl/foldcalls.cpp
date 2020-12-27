// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: foldcalls.cpp
// Author: crdrisko
// Date: 10/30/2020-06:47:08
// Description: Folding the comma operator for calls to member functions of a variadic number of base classes

#include <iostream>

// template for variadic number of base classes
template<typename... Bases>
class MultiBase : private Bases...
{
public:
    void print()
    {
        // call print() of all base classes:
        (..., Bases::print());
    }
};

struct A
{
    void print() { std::cout << "A::print()\n"; }
};

struct B
{
    void print() { std::cout << "B::print()\n"; }
};

struct C
{
    void print() { std::cout << "C::print()\n"; }
};

int main()
{
    MultiBase<A, B, C> mb;
    mb.print();
}
