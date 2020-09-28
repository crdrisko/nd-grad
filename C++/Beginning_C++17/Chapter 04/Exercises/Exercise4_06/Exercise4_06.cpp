// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise4_06.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/26/2020-09:56:04
// Description: Determining where a number fits in a range using only the conditional operator

#include <iostream>

int main()
{
    int number {};
    std::cout << "Enter an integer number: ";
    std::cin  >> number;

    std::cout << "The number is "
              << ( (number <=  20) ? "less than or equal to 20."
                 : (number <=  30) ? "greater than 20 but less than or equal to 30."
                 : (number <= 100) ? "greater than 30 but less than or equal to 100."
                 : "greater than 100." ) << std::endl;
}
