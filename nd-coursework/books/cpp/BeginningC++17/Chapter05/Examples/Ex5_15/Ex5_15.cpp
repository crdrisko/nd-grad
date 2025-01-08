// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex5_15.cpp
// Author: crdrisko
// Date: 04/29/2020-16:37:44
// Description: Sorting an array in ascending sequence -using a vector<T> container

#include <iomanip>
#include <iostream>
#include <vector>

int main()
{
    std::vector<double> x;   // Stores data to be sorted

    while (true)
    {
        double input {};   // Temporary store for a value
        std::cout << "Enter a non-zero value, or 0 to end: ";
        std::cin >> input;

        if (input == 0)
            break;

        x.push_back(input);
    }

    if (x.empty())
    {
        std::cout << "Nothing to sort ..." << std::endl;
        return 0;
    }

    std::cout << "Starting sort." << std::endl;

    while (true)
    {
        bool swapped {false};   // Becomes true when not all values are in order
        for (std::size_t i {}; i < x.size() - 1; ++i)
        {
            if (x[i] > x[i + 1])   // Out of order so swap them
            {
                const auto temp = x[i];
                x[i]            = x[i + 1];
                x[i + 1]        = temp;
                swapped         = true;
            }
        }

        if (!swapped)   // If there were no swaps ...
            break;      // ... all values are in order ...
    }                   // ... otherwise, go round again

    std::cout << "Your data in ascending sequence:\n" << std::fixed << std::setprecision(1);
    const std::size_t perline {10};   // Number output per line
    std::size_t n {};                 // Number on current line
    for (std::size_t i {}; i < x.size(); ++i)
    {
        std::cout << std::setw(8) << x[i];
        if (++n == perline)   // When perline have been written ...
        {
            std::cout << std::endl;   // ... start a new line and ...
            n = 0;                    // ... reset the count on this line
        }
    }
    std::cout << std::endl;
}
