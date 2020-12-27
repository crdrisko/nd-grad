// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: parforeachloop.cpp
// Author: crdrisko
// Date: 11/11/2020-07:07:11
// Description: Comparing the parallel for_each algorithm to the sequential version

#include <algorithm>
#include <cmath>                                            // for std::sqrt()
#include <cstdlib>                                          // for std::atoi()
#include <execution>                                        // for execution policy
#include <iostream>
#include <numeric>
#include <vector>

#include "timer.hpp"

int main(int argc, char* argv[])
{
    // numElems from the command line (default: 1000)
    int numElems = 1000;
    if (argc > 1)
        numElems = std::atoi(argv[1]);

    struct Data
    {
        double value;                                       // initial value
        double sqrt;                                        // parallel computed square root
    };

    // initialize numElems values without square root:
    std::vector<Data> coll;
    coll.reserve(numElems);

    for (int i = 0; i < numElems; ++i)
        coll.push_back(Data {i * 4.37, 0});

    // loop to make measurements mature:
    for (int i {0}; i < 5; ++i)
    {
        Timer t;

        // sequential execution:
        std::for_each(/* std::execution::seq, */ coll.begin(), coll.end(), [](auto& val) { val.sqrt = std::sqrt(val.value); });
        t.printDiff("sequential: ");

        // parallel execution:
        std::for_each(/* std::execution::par, */ coll.begin(), coll.end(), [](auto& val) { val.sqrt = std::sqrt(val.value); });
        t.printDiff("parallel:   ");

        std::cout << '\n';
    }
}
