// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex8_09B.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/13/2020-08:18:57
// Description: Passing an array to a function - pass by reference improved

#include <array>                                            // For std::size()
#include <iostream>

double average10(const double (&)[10]);                     // Function prototype

int main()
{
    double values[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
    // double values[] { 1.0, 2.0, 3.0 };                      // Only three values!!!
    std::cout << "Average = " << average10(values) << std::endl;
}

// Function to compute an average
double average10(const double (&array)[10])
{
    double sum {};                                          // Accumulate total in here
    for (double val : array)
        sum += val;                                         // Sum array elements
    return sum / std::size(array);                          // Return average
}