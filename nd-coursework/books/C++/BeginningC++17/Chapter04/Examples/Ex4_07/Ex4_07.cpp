// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex4_07.cpp
// Author: cdrisko
// Date: 04/25/2020-11:55:24
// Description: Using the switch statement

#include <iostream>

int main()
{
    int choice {};                      // Stores selection value

    std::cout << "Your electronic recipe book is at your service.\n"
              << "You can choose from the following delicious dishes:\n"
              << "1  Boiled eggs\n"
              << "2  Fried eggs\n"
              << "3  Scrambled eggs\n"
              << "4  Coddled eggs\n"
              << "Enter your selection number: ";
    std::cin  >> choice;

    switch (choice)
    {
    case 1:
        std::cout << "Boil some eggs." << std::endl;
        break;
    case 2:
        std::cout << "Fry some eggs." << std::endl;
        break;
    case 3:
        std::cout << "Scramble some eggs." << std::endl;
        break;
    case 4:
        std::cout << "Coddle some eggs." << std::endl;
        break;
    default:
        std::cout << "You entered a wrong number - try raw eggs." << std::endl;
    }
}
