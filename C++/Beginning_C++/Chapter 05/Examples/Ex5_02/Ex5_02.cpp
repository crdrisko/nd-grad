// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for license information.
//
// Name: Ex5_02.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/26/2020-14:48:59
// Description: Obtaining the number of array elements

#include <array>                    // For std::size()
#include <iostream>

int main()
{
    int values[] {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

    std::cout << "There are " << sizeof(values) / sizeof(values[0])
              << " elements in the array." << std::endl;

    int sum {};
    for (std::size_t i {}; i < std::size(values); ++i)
    {
        sum += values[i];
    }
    std::cout << "The sum of the array elements is " << sum << std::endl;
}
