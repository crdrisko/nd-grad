// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex2_04.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/22/2020-13:58:30
// Description: Using explicit type conversions

#include <iostream>

int main()
{
    const unsigned feet_per_yard {3};
    const unsigned inches_per_foot {12};

    double length {};                       // Length as decimal yards
    unsigned int yards  {};                 // Whole yards
    unsigned int feet   {};                 // Whole feet
    unsigned int inches {};                 // Whole inches

    std::cout << "Enter a length in yards as a decimal: ";
    std::cin  >> length;

    // Get the length as yards, feet, and inches
    yards  = static_cast<unsigned int>(length);
    feet   = static_cast<unsigned int>((length - yards) * feet_per_yard);
    inches = static_cast<unsigned int>
                            (length * feet_per_yard * inches_per_foot) % inches_per_foot;

    std::cout << length << " yards converts to "
              << yards  << " yards "
              << feet   << " feet "
              << inches << " inches." << std::endl;
}
