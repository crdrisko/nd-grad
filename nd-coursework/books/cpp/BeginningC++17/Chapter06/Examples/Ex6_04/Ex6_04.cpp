// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex6_04.cpp
// Author: crdrisko
// Date: 04/30/2020-22:04:40
// Description: Using an array of pointers

#include <array>   // For std::size()
#include <iostream>

int main()
{
    const char* pstars[] {"Fatty Arbuckle",
        "Clara Bow",
        "Lassie",
        "Slim Pickens",
        "Boris Karloff",
        "Mae West",
        "Oliver Hardy",
        "Greta Garbo"};

    std::cout << "Pick a lucky star! Enter a number between 1 and " << std::size(pstars) << ": ";
    std::size_t choice {};
    std::cin >> choice;

    if (choice >= 1 && choice <= std::size(pstars))
    {
        std::cout << "Your lucky star is " << pstars[choice - 1] << std::endl;
    }
    else
    {
        std::cout << "Sorry, you haven't got a lucky star." << std::endl;
    }
}
