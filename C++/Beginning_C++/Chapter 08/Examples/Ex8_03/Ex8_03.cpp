// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex8_03.cpp - Version 1.0.0
// Author: cdrisko
// Date: 08/10/2020-07:51:21
// Description: Failing to modify the original value of a function argument

#include <iostream>

double changeIt(double value_to_be_changed);                // Function prototype

int main()
{
    double it {5.0};
    double result {changeIt(it)};

    std::cout << "After function execution, it = " << it
              << "\nResult returned is " << result << std::endl;
}

// Function that attempts to modify an argument and return it
double changeIt(double it)
{
    it += 10.0;                                             // This modifies the copy
    std::cout << "Within function, it = " << it << std::endl;
    return it;
}
