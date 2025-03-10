// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex8_05.cpp
// Author: crdrisko
// Date: 08/10/2020-08:01:47
// Description: Passing an array to a function

#include <array>   // For std::size()
#include <iostream>

double average(double array[], std::size_t count);   // Function prototype

int main()
{
    double values[] {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    std::cout << "Average = " << average(values, std::size(values)) << std::endl;
}

// Function to compute an average
double average(double array[], std::size_t count)
{
    double sum {};   // Accumulate total in here
    for (std::size_t i {}; i < count; ++i)
        sum += array[i];   // Sum array elements
    return sum / count;    // Return average
}
