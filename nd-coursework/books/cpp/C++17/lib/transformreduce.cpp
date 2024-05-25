// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: transformreduce.cpp
// Author: crdrisko
// Date: 11/17/2020-07:06:27
// Description: An example of how to use the new algorithm std::transform_reduce()

#include <array>
#include <functional>
#include <iostream>
#include <numeric>

int main()
{
    std::array coll {3, 1, 7, 5, 4, 1, 6, 3};

    auto twice = [](int v) { return v * 2; };

    // process sum of doubled values of elements:
    std::cout << "sum of doubles: "
              << std::transform_reduce(coll.cbegin(),
                     coll.cend(),   // range
                     0,
                     std::plus {},
                     twice)
              << '\n';

    // process sum of squared values:
    std::cout << "sum of squared: "
              << std::transform_reduce(coll.cbegin(),
                     coll.cend(),   // range
                     0L,
                     std::plus {},
                     [](auto v) { return v * v; })
              << '\n';
}
