// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex8_06.cpp
// Author: crdrisko
// Date: 08/12/2020-07:40:58
// Description: Passing a two-dimensional array to a function

#include <array>                                            // For std::size()
#include <iostream>

double yield(const double values[][4], std::size_t n);

int main()
{
    double beans[3][4] { { 1.0,  2.0,  3.0,  4.0 },
                         { 5.0,  6.0,  7.0,  8.0 },
                         { 9.0, 10.0, 11.0, 12.0 } };

    std::cout << "Yield = " << yield(beans, std::size(beans)) << std::endl;
}

// Function to compute total yield
double yield(const double array[][4], std::size_t size)
{
    double sum {};
    for (std::size_t i {}; i < size; ++i)                   // Loop through rows
    {
        for (std::size_t j {}; j < 4; ++j)                  // Loop through elements in a row
        {
            sum += array[i][j];
        }
    }
    return sum;
}
