// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: compressedtuple1.cpp
// Author: crdrisko
// Date: 12/05/2020-08:05:08
// Description: Testing how well our tuple handles it's storage

#include <iostream>

#include "tuplestorage3.hpp"

struct A
{
    A() { std::cout << "A()\n"; }
};

struct B
{
    B() { std::cout << "B()\n"; }
};

int main()
{
    Tuple<A, char, A, char, B> t1;

    std::cout << sizeof(t1) << " bytes\n";
}
