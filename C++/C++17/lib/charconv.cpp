// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: charconv.cpp
// Author: crdrisko
// Date: 11/01/2020-11:41:04
// Description: Using to_chars and from_chars to show that the round-trip always results in the same initial value

#include "charconv.hpp"

#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    std::vector<double> coll {0.1, 0.3, 0.00001};

    // create two slightly different floating-point values:
    auto sum1 = std::accumulate(coll.begin(), coll.end(), 0.0, std::plus<>());
    auto sum2 = std::accumulate(coll.rbegin(), coll.rend(), 0.0, std::plus<>());

    // look the same:
    std::cout << "sum1:  " << sum1 << '\n';
    std::cout << "sum2:  " << sum2 << '\n';

    // but are different:
    std::cout << std::boolalpha << std::setprecision(20);
    std::cout << "equal: " << (sum1 == sum2) << '\n';   // false !!
    std::cout << "sum1:  " << sum1 << '\n';
    std::cout << "sum2:  " << sum2 << '\n';
    std::cout << '\n';

    // check round-trip:
    d2str2d(sum1);
    d2str2d(sum2);
}
