// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise2_06.cpp
// Author: cdrisko
// Date: 04/23/2020-12:09:55
// Description: Find which entered value is largest and smallest without any decision-making facilities

#include <iostream>

int main()
{
    long a {}, b {};
    std::cout << "Enter two integers separated by spaces: ";
    std::cin  >> a >> b;

    const long larger  = ( (a * (a / b) + b * (b / a)) ) / ( (a / b) + (b / a) );
    const long smaller = ( (a * (b / a) + b * (a / b)) ) / ( (a / b) + (b / a) );

    std::cout << "The larger value is "       << larger
              << " and the smaller value is " << smaller << std::endl;
}
