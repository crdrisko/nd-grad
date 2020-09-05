// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex8_09C.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/13/2020-08:19:03
// Description: Passing an array to a function - use std::array<>

#include <array>
#include <iostream>

double average10(const std::array<double, 10>& array);      // Function prototype

int main()
{
    std::array<double, 10> values { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
    // std::array<double, 3> values { 1.0, 2.0, 3.0 };         // Only three values!!!
    std::cout << "Average = " << average10(values) << std::endl;
}

// Function to compute an average
double average10(const std::array<double, 10>& array)
{
    double sum {};                                          // Accumulate total in here
    for (double val : array)
        sum += val;                                         // Sum array elements
    return sum / array.size();                              // Return average
}
