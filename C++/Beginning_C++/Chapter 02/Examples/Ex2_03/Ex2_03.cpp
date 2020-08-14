// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for license information.
//
// Name: Ex2_03.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/22/2020-13:47:25
// Description: Sizing a pond for happy fish

#include <cmath>                            // For square root function
#include <iostream>

int main()
{
    // 2 square feet pond surface for every 6 inches of fish
    const double fish_factor {2.0 / 0.5};   // Area per unit length of fish
    const double inches_per_foot {12.0};
    const double pi {3.141592653589793238};

    double fish_count {};                   // Number of fish
    double fish_length {};                  // Average length of fish

    std::cout << "Enter the number of fish you want to keep: ";
    std::cin  >> fish_count;
    std::cout << "Enter the average fish length in inches: ";
    std::cin  >> fish_length;
    fish_length /= inches_per_foot;         // Convert to feet

    // Calculate the required surface area
    const double pond_area {fish_count * fish_length * fish_factor};

    // Calculate the pond diameter from the area
    const double pond_diameter {2.0 * std::sqrt(pond_area/pi)};

    std::cout << "\nPond diameter required for " << fish_count << " fish is "
              << pond_diameter << " feet.\n";
}
