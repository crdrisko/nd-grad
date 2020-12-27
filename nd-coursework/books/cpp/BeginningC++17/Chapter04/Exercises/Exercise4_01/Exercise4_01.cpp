// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise4_01.cpp
// Author: cdrisko
// Date: 04/25/2020-12:55:34
// Description: Determine if two values are equal

#include <iostream>

int main()
{
    int a {}, b {};
    std::cout << "Enter two integers separated by spaces: ";
    std::cin  >> a >> b;

    if (a == b)
        std::cout << "The two integers are the same." << std::endl;
    else
        std::cout << "The two integers are not the same." << std::endl;
}
