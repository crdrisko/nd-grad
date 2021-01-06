// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise6_05.cpp
// Author: cdrisko
// Date: 05/02/2020-11:27:26
// Description: Dynamically allocating an array using smart pointers to approximate pi

#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>

int main()
{
    std::size_t size {};
    std::cout << "Enter an array size: ";
    std::cin  >> size;

    auto values { std::make_unique<double[]>(size) };
    double sum {};

    for (std::size_t i {}; i < size; ++i)
    {
        values[i] = 1 / std::pow(i + 1, 2);
        sum += values[i];
    }

    std::cout << "The result is " << std::setprecision(15) << std::sqrt(6.0 * sum) << std::endl;
}

