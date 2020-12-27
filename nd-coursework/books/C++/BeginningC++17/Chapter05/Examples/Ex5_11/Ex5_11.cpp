// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex5_11.cpp
// Author: cdrisko
// Date: 04/29/2020-12:50:04
// Description: Working with strings in an array

#include <array>                        // For std::size()
#include <iostream>

int main()
{
    const std::size_t max_length {80};       // Maximum string length (including \0)
    char stars[][max_length] {
                                "Fatty Arbuckle",   "Clara Bow",
                                "Lassie",           "Slim Pickens",
                                "Boris Karloff",    "Mae West",
                                "Oliver Hardy",     "Greta Garbo"
                             };
    std::size_t choice {};

    std::cout << "Pick a lucky star! Enter a number between 1 and "
              << std::size(stars) << ": ";
    std::cin  >> choice;

    if (choice >= 1 && choice <= std::size(stars))
    {
        std::cout << "Your lucky star is " << stars[choice - 1] << std::endl;
    }
    else
    {
        std::cout << "Sorry, you haven't got a lucky star." << std::endl;
    }
}
