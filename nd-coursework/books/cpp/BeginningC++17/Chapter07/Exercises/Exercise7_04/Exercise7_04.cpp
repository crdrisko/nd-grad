// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise7_04.cpp
// Author: cdrisko
// Date: 08/04/2020-07:41:03
// Description: Determining whether two input words (no spaces) are anagrams of one another

#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>

int main()
{
    std::string string1;
    std::cout << "Enter the first word: ";
    std::cin  >> string1;

    std::string string2;
    std::cout << "Enter the second word: ";
    std::cin  >> string2;

    bool isAnagram {false};

    if ( string1.length() == string2.length() )
    {
        std::string lowercaseString1, lowercaseString2;

        // Convert to lowercase and sort the first string
        for (const auto& ch : string1)
            lowercaseString1.push_back( std::tolower(ch) );

        while (true)
        {
            bool swapped {false};

            for (std::size_t i {}; i < lowercaseString1.length() - 1; ++i)
            {
                if (lowercaseString1[i] > lowercaseString1[i + 1])
                {
                    const auto temp = lowercaseString1[i];

                    lowercaseString1[i] = lowercaseString1[i + 1];
                    lowercaseString1[i + 1] = temp;
                    swapped = true;
                }
            }

            if (!swapped)
                break;
        }

        // Convert to lowercase and sort the second string
        for (const auto& ch : string2)
            lowercaseString2.push_back( std::tolower(ch) );

        while (true)
        {
            bool swapped {false};

            for (std::size_t i {}; i < lowercaseString2.length() - 1; ++i)
            {
                if (lowercaseString2[i] > lowercaseString2[i + 1])
                {
                    const auto temp = lowercaseString2[i];

                    lowercaseString2[i] = lowercaseString2[i + 1];
                    lowercaseString2[i + 1] = temp;
                    swapped = true;
                }
            }

            if (!swapped)
                break;
        }

        if (lowercaseString1 == lowercaseString2)
            isAnagram = true;
    }

    std::cout << string1 << " is " << ( (isAnagram) ? "" : "not " )
              << "an anagram of " << string2 << "." << std::endl;
}
