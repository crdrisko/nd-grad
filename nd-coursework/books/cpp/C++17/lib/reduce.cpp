// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: reduce.cpp
// Author: crdrisko
// Date: 11/17/2020-06:59:50
// Description: An example of how to use the new algorithm std::reduce()

#include <array>
#include <functional>
#include <iostream>
#include <numeric>

int main()
{
    std::array coll {3, 1, 7, 5, 4, 1, 6, 3};

    // process sum of elements:
    std::cout << "sum: " << std::reduce(coll.begin(), coll.end())   // range
              << '\n';

    // process sum of elements with initial value:
    std::cout << "sum: "
              << std::reduce(coll.begin(),
                     coll.end(),   // range
                     0)            // initial value
              << '\n';

    // process product of elements:
    std::cout << "product: "
              << std::reduce(coll.begin(),
                     coll.end(),           // range
                     1LL,                  // initial value
                     std::multiplies {})   // operation
              << '\n';

    // process product of elements (use 0 as initial value):
    std::cout << "product: "
              << std::reduce(coll.begin(),
                     coll.end(),           // range
                     0,                    // initial value
                     std::multiplies {})   // operation
              << '\n';
}
