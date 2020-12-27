// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: vartmplauto2.cpp
// Author: crdrisko
// Date: 10/31/2020-15:25:10
// Description: Definition of the printArr() function which accesses the now modified global array elements

#include <iostream>

#include "vartmplauto.hpp"

void printArr()
{
    std::cout << "arr<int, 5>:  ";

    for (const auto& elem : arr<int, 5>)
        std::cout << elem << ' ';
    std::cout << "\narr<int, 5u>: ";

    for (const auto& elem : arr<int, 5u>)
        std::cout << elem << ' ';
    std::cout << '\n';
}
