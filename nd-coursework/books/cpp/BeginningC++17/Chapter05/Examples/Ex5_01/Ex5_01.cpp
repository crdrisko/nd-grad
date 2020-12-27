// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex5_01.cpp
// Author: cdrisko
// Date: 04/26/2020-14:44:30
// Description: Using a for loop with an array

#include <iostream>

int main()
{
    const unsigned size {6};                            // Array size
    unsigned height[size] {26, 37, 47, 55, 62, 75};     // An array of heights

    unsigned total {};                                  // Sum of heights
    for (std::size_t i {}; i < size; ++i)
    {
        total += height[i];
    }

    const unsigned average {total/size};                // Calculate average height
    std::cout << "The average height is " << average << std::endl;

    unsigned count {};
    for (std::size_t i {}; i < size; ++i)
    {
        if (height[i] < average) ++count;
    }
    std::cout << count << " people are below average height." << std::endl;
}
