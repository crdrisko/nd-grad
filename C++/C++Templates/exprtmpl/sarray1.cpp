// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: sarray1.cpp
// Author: crdrisko
// Date: 09/27/2020-11:48:40
// Description: Evaluating an example numeric expression with our simple arrays

#include "sarray1.hpp"
#include "sarrayops1.hpp"

int main()
{
    SArray<double> x(1000), y(1000);
    //...
    x = 1.2*x + x*y;
}
