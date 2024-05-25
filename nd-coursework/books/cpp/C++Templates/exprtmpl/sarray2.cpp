// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: sarray2.cpp
// Author: crdrisko
// Date: 09/28/2020-09:43:52
// Description: Rewriting our desired computation using operation-assignment operators

#include "sarray2.hpp"

#include "sarrayops2.hpp"

int main()
{
    SArray<double> x(1000), y(1000);
    // ...
    // process x = 1.2*x + x*y;

    SArray<double> tmp(x);
    tmp *= y;
    x *= 1.2;
    x += tmp;
}
