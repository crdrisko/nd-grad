// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise4_02.cpp
// Author: cdrisko
// Date: 04/25/2020-13:00:49
// Description: Finding if two positive, nonzero integers are multiples

#include <iostream>

int main()
{
    int a {}, b {};
    std::cout << "Enter two positive, non-zero integers separated by spaces: ";
    std::cin  >> a >> b;

    if (a > 0 && b > 0)
    {
        int larger  { (a > b) ? a : b };
        int smaller { (a > b) ? b : a };

        if ( !(larger % smaller) )
            std::cout << smaller << " is a multiple of " << larger << std::endl;
        else
            std::cout << smaller << " is not a multiple of " << larger << std::endl;
    }
    else
        std::cout << "The input must be two positive, non-zero integers." << std::endl;
}
