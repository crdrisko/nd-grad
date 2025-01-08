// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex2_05.cpp
// Author: crdrisko
// Date: 04/22/2020-14:05:32
// Description: Finding maximum and minimum values for data types

#include <iostream>
#include <limits>

int main()
{
    std::cout << "The range for type short is from " << std::numeric_limits<short>::min() << " to "
              << std::numeric_limits<short>::max() << std::endl;
    std::cout << "The range for type int is from " << std::numeric_limits<int>::min() << " to "
              << std::numeric_limits<int>::max() << std::endl;
    std::cout << "The range for type long is from " << std::numeric_limits<long>::min() << " to "
              << std::numeric_limits<long>::max() << std::endl;
    std::cout << "The range for type float is from " << std::numeric_limits<float>::min() << " to "
              << std::numeric_limits<float>::max() << std::endl;
    std::cout << "The range for type double is from " << std::numeric_limits<double>::min() << " to "
              << std::numeric_limits<double>::max() << std::endl;
    std::cout << "The range for type long double is from " << std::numeric_limits<long double>::min() << " to "
              << std::numeric_limits<long double>::max() << std::endl;
}
