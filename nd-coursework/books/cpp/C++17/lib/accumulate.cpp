// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: accumulate.cpp
// Author: crdrisko
// Date: 11/11/2020-07:07:37
// Description: An example use of std::accumulate()

#include <iostream>
#include <numeric>   // for std::accumulate()
#include <vector>

void printSum(long num)
{
    // create coll with num sequences of 1 2 3 4:
    std::vector<long> coll;
    coll.reserve(num * 4);

    for (long i = 0; i < num; ++i)
        coll.insert(coll.end(), {1, 2, 3, 4});

    auto sum = std::accumulate(coll.begin(), coll.end(), 0L);

    std::cout << "accumulate(): " << sum << '\n';
}

int main()
{
    printSum(1);
    printSum(1000);
    printSum(1000000);
    printSum(10000000);
}
