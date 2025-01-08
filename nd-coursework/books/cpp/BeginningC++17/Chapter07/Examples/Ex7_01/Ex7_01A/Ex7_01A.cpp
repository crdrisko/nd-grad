// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex7_01A.cpp
// Author: crdrisko
// Date: 05/03/2020-15:07:05
// Description: Concatenating characters and strings

#include <iostream>
#include <string>

int main()
{
    std::string first;    // Stores the first name
    std::string second;   // Stores the second name

    std::cout << "Enter your first name: ";
    std::cin >> first;   // Read first name

    std::cout << "Enter your second name: ";
    std::cin >> second;   // Read second name

    std::string sentence {"Your full name is "};   // Create basic sentence
    sentence += first + ' ' + second + '.';        // Augment with names

    std::cout << sentence << std::endl;   // Output the sentence
    std::cout << "The string contains "   // Output its length
              << sentence.length() << " characters." << std::endl;
}
