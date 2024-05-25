// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: accumulate2.cpp
// Author: crdrisko
// Date: 11/17/2020-06:15:19
// Description: Another example use of std::accumulate() but this time with a non-associative operation

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

    auto squaredSum = [](auto sum, auto val) { return sum + val * val; };

    auto sum = std::accumulate(coll.begin(), coll.end(), 0L, squaredSum);

    std::cout << "accumulate(): " << sum << '\n';
}

int main()
{
    printSum(1);
    printSum(1000);
    printSum(1000000);
    printSum(10000000);
}
