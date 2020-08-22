// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex5_12.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/29/2020-12:57:02
// Description: Allocating an array at runtime

#include <iomanip>                      // For std::setprecision()
#include <iostream>

int main()
{
    std::size_t count {};
    std::cout << "How many heights will you enter? ";
    std::cin  >> count;
    int height[count];                  // Create the array of count elements

    // Read the heights
    std::size_t entered {};
    while (entered < count)
    {
        std::cout << "Enter a height: ";
        std::cin  >> height[entered];
        if (height[entered] > 0)        // Make sure value is positive
        {
            ++entered;
        }
        else
        {
            std::cout << "A height must be positive - try again.\n";
        }
    }

    // Calculate the sum of the heights
    unsigned int total {};
    for (std::size_t i {}; i < count; ++i)
    {
        total += height[i];
    }

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "The average height is " << static_cast<float>(total) / count << std::endl;
}
