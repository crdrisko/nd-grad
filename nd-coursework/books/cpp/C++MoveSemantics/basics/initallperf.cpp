// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: initallperf.cpp
// Author: crdrisko
// Date: 08/05/2021-07:55:23
// Description: Comparing initialized members via Rvalue references to the other approaches

#include <cstdlib>   // for std::atoi()
#include <iostream>

#define USE_ALL

#include "initall.hpp"
#include "initmeasure.hpp"

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
    std::cout << num << " iterations take: " << msDur.count() << "ms\n";
    std::cout << "3 inits take on average: " << nsDur.count() / num << "ns\n";
}
