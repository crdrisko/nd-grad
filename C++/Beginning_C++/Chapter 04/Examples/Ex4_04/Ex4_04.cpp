// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex4_04.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/25/2020-08:51:45
// Description: Using the if-else statement

#include <iostream>

int main()
{
    long number {};                             // Stores input
    std::cout << "Enter an integer less than 2 billion: ";
    std::cin  >> number;

    if (number % 2)                             // Test remainder after division by 2
    {   // Here if remainder is 1
        std::cout << "Your number is odd." << std::endl;
    }
    else
    {   // Hese if remainder is 0
        std::cout << "Your number is even." << std::endl;
    }
}
