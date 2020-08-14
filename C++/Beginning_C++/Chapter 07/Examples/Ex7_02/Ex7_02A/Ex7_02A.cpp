// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for license information.
//
// Name: Ex7_02A.cpp - Version 1.0.0
// Author: cdrisko
// Date: 05/03/2020-15:11:25
// Description: Accessing characters in a string with a range-based for loop

#include <cctype>
#include <iostream>
#include <string>

int main()
{
    std::string text;                                           // Stores the input
    std::cout << "Enter a line of text:\n";
    std::getline(std::cin, text);                               // Read a line including spaces

    unsigned vowels {};                                         // Count of vowels
    unsigned consonants {};                                     // Count of consonants
    for (const auto& ch : text)
    {
        if (std::isalpha(ch))
        {
            switch (std::tolower(ch))                           // Convert to lowercase
            {
            case 'a': case 'e': case 'i': case 'o': case 'u':
                ++vowels;
                break;

            default:
                ++consonants;
                break;
            }
        }
    }

    std::cout << "Your input contained " << vowels << " vowels and "
              << consonants << " consonants." << std::endl;
}
