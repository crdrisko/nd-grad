// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex8_02.cpp
// Author: cdrisko
// Date: 08/07/2020-14:55:10
// Description: Calculating powers - rearranged

#include <iomanip>
#include <iostream>

int main()
{
    // Calculating powers of 8 from -3 to +3
    for (int i {-3}; i <= 3; ++i)
        std::cout << std::setw(10) << power(8.0, i);

    std::cout << std::endl;
}

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
