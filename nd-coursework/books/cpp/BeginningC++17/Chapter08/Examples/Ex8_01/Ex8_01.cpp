// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex8_01.cpp
// Author: crdrisko
// Date: 08/07/2020-14:47:53
// Description: Calculating powers

#include <iomanip>
#include <iostream>

// Function to calculate x to the power n
double power(double x, int n)
{
    double result {1.0};

    if (n >= 0)
    {
        for (int i {1}; i <= n; ++i)
            result *= x;
    }
    else   // n < 0
    {
        for (int i {1}; i <= -n; ++i)
            result /= x;
    }

    return result;
}

int main()
{
    // Calculate powers of 8 from -3 to +3
    for (int i {-3}; i <= 3; ++i)
        std::cout << std::setw(10) << power(8.0, i);

    std::cout << std::endl;
}
