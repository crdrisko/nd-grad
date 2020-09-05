// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex8_09A.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/13/2020-08:18:52
// Description: Passing an array to a function - pass by reference

#include <iostream>

double average10(const double (&)[10]);                     // Function prototype

int main()
{
    // Use 10 values to make example compile...
    // double values[] { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
    double values[] { 1.0, 2.0, 3.0 };                      // Only three values!!!
    std::cout << "Average = " << average10(values) << std::endl;
}

// Function to compute an average
double average10(const double (&array)[10])                 // Only arrays of length 10 can be passed!
{
    double sum {};                                          // Accumulate total in here
    for (std::size_t i {}; i < 10; ++i)
        sum += array[i];                                    // Sum array elements
    return sum / 10;                                        // Return average
}
