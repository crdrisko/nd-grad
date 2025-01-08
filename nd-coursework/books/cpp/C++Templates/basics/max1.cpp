// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: max1.cpp
// Author: crdrisko
// Date: 07/25/2020-20:36:07
// Description: Using the max() function template

#include "max1.hpp"

#include <iostream>
#include <string>

int main()
{
    int i = 42;
    std::cout << "max(7, i):    " << ::max(7, i) << '\n';

    double f1 = 3.4;
    double f2 = -6.7;
    std::cout << "max(f1, f2):  " << ::max(f1, f2) << '\n';

    std::string s1 = "mathematics";
    std::string s2 = "math";
    std::cout << "max(s1, s2):  " << ::max(s1, s2) << '\n';
}
