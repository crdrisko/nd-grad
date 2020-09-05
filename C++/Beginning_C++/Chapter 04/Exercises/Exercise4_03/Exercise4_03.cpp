// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise4_03.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/25/2020-13:19:58
// Description: Check how a number between 1 and 100 compares to 50

#include <iostream>

int main()
{
    double number {};
    std::cout << "Enter a number between 1 and 100: ";
    std::cin  >> number;

    if (number >= 1 && number <= 100)
    {
        std::cout << "Your number is ";

        if (number > 50)
            std::cout << "greater than 50." << std::endl;
        else if (number < 50)
            std::cout << "less than 50." << std::endl;
        else
            std::cout << "equal to 50." << std::endl;
    }
    else
        std::cout << "The program requires a number between 1 and 100." << std::endl;
}
