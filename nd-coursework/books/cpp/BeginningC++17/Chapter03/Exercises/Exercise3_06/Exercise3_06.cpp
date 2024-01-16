// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise3_06.cpp
// Author: cdrisko
// Date: 04/23/2020-14:55:57
// Description: Swap two values without defining a third placeholder value

#include <iostream>

int main()
{
    long a {}, b {};
    std::cout << "Enter two integers separated by spaces: ";
    std::cin  >> a >> b;

    a ^= b;
    b ^= a;
    a ^= b;

    std::cout << "In reverse order that is: " << a << " " << b << std::endl;
}
