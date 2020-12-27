// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise3_02.cpp
// Author: cdrisko
// Date: 04/23/2020-14:32:15
// Description: Determine the number of square boxes that can fit on a rectangular shelf

#include <iostream>

int main()
{
    const unsigned int inches_per_foot {12};

    double shelfLength {}, shelfDepth {};
    std::cout << "Enter the dimensions of the shelf, length followed by depth in feet: ";
    std::cin  >> shelfLength >> shelfDepth;

    int boxSide {};
    std::cout << "Enter the length of the box's side in inches: ";
    std::cin  >> boxSide;

    // Round down here since we don't want any overhang
    long shelfArea = static_cast<long>( (shelfLength * inches_per_foot) * (shelfDepth * inches_per_foot) );
    long boxArea = boxSide * boxSide;

    long numberOfBoxes = shelfArea / boxArea;

    std::cout << "The number of square boxes that can fit on your shelf is " << numberOfBoxes << " boxes." << std::endl;
}
