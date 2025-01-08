// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex4_01.cpp
// Author: crdrisko
// Date: 04/24/2020-13:41:26
// Description: Comparing data values

#include <iostream>

int main()
{
    char first {};    // Stores the first character
    char second {};   // Stores the second character

    std::cout << "Enter a character: ";
    std::cin >> first;

    std::cout << "Enter a second character: ";
    std::cin >> second;

    // std::cout << std::boolalpha;             // Uncomment for true or false instead of 1 or 0

    std::cout << "The value of the expression " << first << '<' << second << " is: " << (first < second) << std::endl;
    std::cout << "The value of the expression " << first << "==" << second << " is: " << (first == second) << std::endl;
}
