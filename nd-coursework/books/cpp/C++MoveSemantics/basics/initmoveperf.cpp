// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: initmoveperf.cpp
// Author: crdrisko
// Date: 08/05/2021-08:02:04
// Description: Comparing initialized members via moved parameters passed by value to the other approaches

#include <cstdlib>   // for std::atoi()
#include <iostream>

#define USE_MOVE

#include "initmeasure.hpp"
#include "initmove.hpp"

int main(int argc, const char** argv)
{
    int num = 1000;   // num iterations to measure

    if (argc > 1)
        num = std::atoi(argv[1]);

    // a few iterations to avoid measuring initial behavior:
    measure(5);

    // measure (in integral nano- and floating-point milliseconds):
    std::chrono::nanoseconds nsDur {measure(num)};
    std::chrono::duration<double, std::milli> msDur {nsDur};

    // print result:
    std::cout << num << "iterations take: " << msDur.count() << "ms\n";
    std::cout << "3 inits take on average:" << nsDur.count() / num << "ns\n";
}
