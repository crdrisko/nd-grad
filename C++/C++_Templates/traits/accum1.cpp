// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: accum1.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/17/2020-10:19:11
// Description: Using the accumulator function template to find averages of arrays

#include <iostream>

#include "accum1.hpp"

int main()
{
    // create array of 5 integer values
    int num[] = { 1, 2, 3, 4, 5 };

    // print average value
    std::cout << "the average value of the integer value is "
              << accum(num, num + 5) / 5
              << '\n';

    // create array of character values
    char name[] = "templates";
    int length = sizeof(name) - 1;

    // (try to) print average character value
    std::cout << "the average value of the characters in \""
              << name << "\" is "
              << accum(name, name + length) / length
              << '\n';
}
