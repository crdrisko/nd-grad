// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise6_03.cpp
// Author: cdrisko
// Date: 05/02/2020-10:59:47
// Description: Dynamically allocating an array using raw pointers to approximate pi

#include <cmath>
#include <iomanip>
#include <iostream>

int main()
{
    std::size_t size {};
    std::cout << "Enter an array size: ";
    std::cin  >> size;

    double* values { new double[size] {} };
    double sum {};

    for (std::size_t i {}; i < size; ++i)
    {
        *(values + i) = 1 / std::pow(i + 1, 2);
        sum += values[i];
    }

    std::cout << "The result is " << std::setprecision(15) << std::sqrt(6.0 * sum) << std::endl;

    delete[] values;
    values = nullptr;
}
