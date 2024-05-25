// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex8_17.cpp
// Author: crdrisko
// Date: 10/23/2020-07:10:55
// Description: Recursive version of function for x to the power n, n positive or negative

#include <iomanip>
#include <iostream>

double power(double x, int n);

int main()
{
    for (int i {-3}; i <= 3; ++i)   // Calculate powers of 8 from -3 to +3
        std::cout << std::setw(10) << power(8.0, i);

    std::cout << std::endl;
}

// Recursive function to calculate x to the power n
double power(double x, int n)
{
    if (n == 0)
        return 1.0;
    else if (n > 0)
        return x * power(x, n - 1);
    else /* n < 0 */
        return 1.0 / power(x, -n);
}
