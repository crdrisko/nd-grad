// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise6_06.cpp
// Author: cdrisko
// Date: 05/02/2020-11:34:05
// Description: Dynamically allocating a vector using smart pointers to approximate pi

#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

int main()
{
    std::size_t size {};
    std::cout << "Enter an array size: ";
    std::cin >> size;

    auto values {std::make_unique<std::vector<double>>()};
    double sum {};

    for (std::size_t i {}; i < size; ++i)
    {
        values->push_back(1 / std::pow(i + 1, 2));
        sum += values->at(i);
    }

    std::cout << "The result is " << std::setprecision(15) << std::sqrt(6.0 * sum) << std::endl;
}
