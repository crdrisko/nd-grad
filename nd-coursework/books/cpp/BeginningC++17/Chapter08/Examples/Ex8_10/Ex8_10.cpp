// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex8_10.cpp
// Author: crdrisko
// Date: 08/14/2020-07:45:38
// Description: Implicit conversions of reference parameters

#include <iostream>

void double_it(double& it) { it *= 2; }
void print_it(const double& it) { std::cout << it << std::endl; }

int main()
{
    double d {123};
    double_it(d);
    print_it(d);

    int i {456};
    // double_it(i);                                           // Error, does not compile
    print_it(i);
}
