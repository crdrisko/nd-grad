// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex7_03.cpp - Version 1.0.0
// Author: cdrisko
// Date: 05/03/2020-15:44:14
// Description: Comparing strings

#include <cctype>                                                   // For character conversion
#include <iomanip>                                                  // For stream manipulators
#include <iostream>                                                 // For stream I/O
#include <string>                                                   // For the string type
#include <vector>                                                   // For the vector container

int main()
{
    std::vector<std::string> names;                                 // Vector of names
    std::string input_name;                                         // Stores a name
    char answer {};                                                 // Response to a prompt

    do
    {
        std::cout << "Enter a name: ";
        std::cin  >> input_name;                                    // Read a name and ...
        names.push_back(input_name);                                // ... add it to the vector

        std::cout << "Do you want to enter another name? (y/n): ";
        std::cin  >> answer;
    } while (std::tolower(answer) == 'y');

    // Sort the names in ascending sequence
    bool sorted {};
    do
    {
        sorted = true;                                              // Remains true when names are sorted
        for (std::size_t i {1}; i < names.size(); ++i)
        {
            if (names[i - 1] > names[i])
            {   // Out of order - so swap names
                names[i].swap(names[i - 1]);
                sorted = false;
            }
        }
    } while (!sorted);

    // Find the length of the longest name
    std::size_t max_length {};
    for (const auto& name : names)
        if (max_length < name.length())
            max_length = name.length();

    // Output the sorted names 5 to a line
    const std::size_t field_width = max_length + 2;
    std::size_t count {};

    std::cout << "In ascending sequence the names you entered are:\n";
    for (const auto& name : names)
    {
        std::cout << std::setw(field_width) << name;
        if (!(++count % 5)) std::cout << std::endl;
    }

    std::cout << std::endl;
}
