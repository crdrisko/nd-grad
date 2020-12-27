// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise2_04.cpp
// Author: cdrisko
// Date: 04/23/2020-11:07:40
// Description: Calculate the height of a tree

#include <cmath>
#include <iostream>

int main()
{
    const double pi {3.141592653589793238};
    const unsigned int inches_per_foot {12};

    double height_eye {};
    std::cout << "Enter the height of your eye in inches: ";
    std::cin  >> height_eye;

    double distance_feet {}, distance_inches {};
    std::cout << "Enter the distance to the tree in feet and inches: ";
    std::cin  >> distance_feet >> distance_inches;

    double angle {};
    std::cout << "Enter the angle between the horizontal and a line to the top of the\n  tree in degrees: ";
    std::cin  >> angle;


    double height_tree = (height_eye / inches_per_foot) + (distance_inches / inches_per_foot + distance_feet)
        * std::tan(angle * (pi / 180));

    std::cout << "The height of that tree is " << height_tree << " feet" << std::endl;
}
