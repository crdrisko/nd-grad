// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex4_03A.cpp
// Author: cdrisko
// Date: 04/24/2020-14:08:26
// Description: Using Standard character classification functions instead of nested ifs

#include <cctype>   // For std::isupper and std::islower
#include <iostream>

int main()
{
    char letter {};                    // Store input here
    std::cout << "Enter a letter: ";   // Prompt for the input
    std::cin >> letter;

    if (std::isupper(letter))
    {
        std::cout << "You entered an uppercase letter." << std::endl;
        return 0;
    }

    if (std::islower(letter))
    {
        std::cout << "You entered a lowercase letter." << std::endl;
        return 0;
    }

    std::cout << "You did not enter a letter." << std::endl;
}
