// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex7_02.cpp - Version 1.0.0
// Author: cdrisko
// Date: 05/03/2020-15:11:20
// Description: Accessing characters in a string

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
    for (std::size_t i {}; i < text.length(); ++i)
    {
        if (std::isalpha(text[i]))
        {
            switch (std::tolower(text[i]))                      // Convert to lowercase
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
