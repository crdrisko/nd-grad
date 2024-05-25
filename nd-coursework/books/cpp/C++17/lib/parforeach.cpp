// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: parforeach.cpp
// Author: crdrisko
// Date: 11/11/2020-07:07:05
// Description: Using a parallel for_each() algorithm

#include <algorithm>
#include <cmath>       // for std::sqrt()
#include <execution>   // for execution policy
#include <iostream>
#include <numeric>
#include <vector>

#include "timer.hpp"

int main()
{
    int numElems = 1000;

    struct Data
    {
        double value;   // initial value
        double sqrt;    // parallel computed square root
    };

    // initialize numElems values without square root:
    std::vector<Data> coll;
    coll.reserve(numElems);

    for (int i = 0; i < numElems; ++i)
        coll.push_back(Data {i * 4.37, 0});

    // parallel computation of square roots:
    std::for_each(/* std::execution::par, */ coll.begin(), coll.end(), [](auto& val) { val.sqrt = std::sqrt(val.value); });
}
