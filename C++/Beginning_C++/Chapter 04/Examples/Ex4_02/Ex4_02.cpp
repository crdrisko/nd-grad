// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for license information.
//
// Name: Ex4_02.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/24/2020-13:53:13
// Description: Using an if statement

#include <iostream>

int main()
{
    std::cout << "Enter an integer between 50 and 100: ";

    int value {};
    std::cin >> value;

    if (value)
        std::cout << "You have entered a value that is different from zero." << std::endl;

    if (value < 50)
        std::cout << "The value is invalid - it is less than 50." << std::endl;

    if (value > 100)
        std::cout << "The value is invalid - it is greater than 100." << std::endl;

    std::cout << "You entered " << value << std::endl;
}
