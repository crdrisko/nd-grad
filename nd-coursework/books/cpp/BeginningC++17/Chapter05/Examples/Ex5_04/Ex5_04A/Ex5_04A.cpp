// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex5_04A.cpp
// Author: crdrisko
// Date: 04/26/2020-15:10:16
// Description: Multiple calculations in a loop expression's third control expression by using the comma operator

#include <iomanip>
#include <iostream>

int main()
{
    unsigned int limit {};
    std::cout << "This program calculates n! and the sum of the integers"
              << " up to n for values 1 to limit.\n";
    std::cout << "What upper limit for n would you like? ";
    std::cin >> limit;

    // Output column headings
    std::cout << std::setw(8) << "integer" << std::setw(8) << " sum" << std::setw(20) << " factorial" << std::endl;

    for (unsigned long long n {1}, sum {1}, factorial {1}; n <= limit; ++n, sum += n, factorial *= n)
    {
        std::cout << std::setw(8) << n << std::setw(8) << sum << std::setw(20) << factorial << std::endl;
    }
}
