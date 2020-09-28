// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise3_01.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/23/2020-14:30:53
// Description: Create a table for the output of a value, it's inverted value, and it's negative

#include <iomanip>
#include <iostream>

int main()
{
    int value {};
    std::cout << "Enter an integer value: ";
    std::cin  >> value;

    int inverted_value {~value};

    std::cout << "|   Value    |   ~Value   | ~Value + 1 |" << std::endl;
    std::cout << "+------------+------------+------------+" << std::endl;

    std::cout << "| " << std::hex << std::showbase << std::internal << std::setfill('0')
              << std::setw(10) << value << " | "
              << std::setw(10) << inverted_value << " | "
              << std::setw(10) << inverted_value + 1 << " |" << std::endl;

    std::cout << "| " << std::dec << std::right << std::setfill(' ')
              << std::setw(10) << value << " | "
              << std::setw(10) << inverted_value << " | "
              << std::setw(10) << inverted_value + 1 << " |" << std::endl;
}
