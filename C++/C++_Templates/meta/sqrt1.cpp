// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: sqrt1.cpp - Version 1.0.0
// Author: crdrisko
// Date: 09/02/2020-08:11:14
// Description: A simple program using our Sqrt template

#include <iostream>

#include "sqrt1.hpp"

int main()
{
    std::cout << "Sqrt<16>::value = " << Sqrt<16>::value << '\n';
    std::cout << "Sqrt<25>::value = " << Sqrt<25>::value << '\n';
    std::cout << "Sqrt<42>::value = " << Sqrt<42>::value << '\n';
    std::cout << "Sqrt<1>::value = " << Sqrt<1>::value << '\n';
}
