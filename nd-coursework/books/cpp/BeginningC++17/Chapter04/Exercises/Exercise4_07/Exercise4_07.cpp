// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise4_07.cpp
// Author: cdrisko
// Date: 04/26/2020-10:12:06
// Description: Using the cctype library to classify properties of a letter

#include <cctype>
#include <iostream>

int main()
{
    char letter {};
    std::cout << "Enter a letter: ";
    std::cin >> letter;

    if (!std::isalpha(letter))
    {
        std::cout << "Required input is a letter." << std::endl;
        return 1;
    }

    // Determining the binary representation of the letter
    unsigned int mask {0b10000000};

    std::cout << "The letter '" << letter << "' (" << (letter & (mask >> 0) ? 1 : 0) << (letter & (mask >> 1) ? 1 : 0)
              << (letter & (mask >> 2) ? 1 : 0) << (letter & (mask >> 3) ? 1 : 0) << (letter & (mask >> 4) ? 1 : 0)
              << (letter & (mask >> 5) ? 1 : 0) << (letter & (mask >> 6) ? 1 : 0) << (letter & (mask >> 7) ? 1 : 0)
              << " in binary) is " << (std::islower(letter) ? "a lowercase" : "an uppercase");

    switch (std::tolower(letter))
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        std::cout << " vowel." << std::endl;
        break;
    default:
        std::cout << " consonant." << std::endl;
        break;
    }

    // A cool way to do this using loops from the next chapter
    // for (int mask {0b10000000}; mask > 0; mask >>= 1)
    //     std::cout << (letter & mask ? 1 : 0);
}
