// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex5_10.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/29/2020-12:40:44
// Description: Classifying the letters in a C-style string

#include <cctype>
#include <iostream>

int main()
{
    const int max_length {100};                     // Array size
    char text[max_length] {};                       // Array to hold input string

    std::cout << "Enter a line of text:" << std::endl;

    // Read a line of characters including spaces
    std::cin.getline(text, max_length);
    std::cout << "You entered:\n" << text << std::endl;

    std::size_t vowels {};                               // Count of vowels
    std::size_t consonants {};                           // Count of consonants
    for (int i {}; text[i] != '\0'; i++)
    {
        if (std::isalpha(text[i]))                  // If it is a letter ...
        {
            switch (std::tolower(text[i]))
            {                                       // ... check lowercase ...
            case 'a': case 'e': case 'i': case 'o': case 'u':
                ++vowels;                           // ... it is a vowel
                break;

            default:
                ++consonants;                       // ... it is a consonant
            }
        }
    }
    std::cout << "Your input contained " << vowels << " vowels and "
              << consonants << " consonants." << std::endl;
}
