// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise2_01.cpp
// Author: cdrisko
// Date: 04/22/2020-14:11:51
// Description: Compute the area of a circle

#include <iostream>

int main()
{
    const float pi {3.14159265f};

    float radius {};
    std::cout << "Enter the radius of the circle: ";
    std::cin >> radius;

    const float area = pi * radius * radius;

    std::cout << "The area of the circle with a radius of " << radius << " is " << area << std::endl;
}
