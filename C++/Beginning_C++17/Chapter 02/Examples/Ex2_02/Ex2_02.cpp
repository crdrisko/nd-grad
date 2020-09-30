// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex2_02.cpp
// Author: cdrisko
// Date: 04/16/2020-12:05:31
// Description: Converting distances

#include <iostream>                             // For output to the screen

int main()
{
    unsigned int yards {}, feet {}, inches {};

    // Convert a distance in yards, feet, and inches to inches
    std::cout << "Enter a distance as yards, feet, and inches "
              << "with the three values separated by spaces:"
              << std::endl;
    std::cin  >> yards >> feet >> inches;

    const unsigned feet_per_yard {3};
    const unsigned inches_per_foot {12};

    unsigned total_inches {};
    total_inches = inches + inches_per_foot * (yards * feet_per_yard + feet);
    std::cout << "The distance corresponds to " << total_inches << " inches.\n";

    // Convert a distance in inches to yards, feet, and inches
    std::cout << "Enter a distance in inches: ";
    std::cin  >> total_inches;
    feet   = total_inches / inches_per_foot;
    inches = total_inches % inches_per_foot;
    yards  = feet / feet_per_yard;
    feet   = feet % feet_per_yard;
    std::cout << "The distance corresponds to "
              << yards  << " yards "
              << feet   << " feet "
              << inches << " inches." << std::endl;
}
