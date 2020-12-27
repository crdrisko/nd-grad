// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise6_04.cpp
// Author: cdrisko
// Date: 05/02/2020-11:13:46
// Description: Dynamically allocating a vector using raw pointers to approximate pi

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int main()
{
    std::size_t size {};
    std::cout << "Enter an array size: ";
    std::cin  >> size;

    auto* values { new std::vector<double> };
    double sum {};

    for (std::size_t i {}; i < size; ++i)
    {
        values->push_back( 1 / std::pow(i + 1, 2) );
        sum += values->at(i);
    }

    std::cout << "The result is " << std::setprecision(15) << std::sqrt(6.0 * sum) << std::endl;

    delete values;
    values = nullptr;
}
