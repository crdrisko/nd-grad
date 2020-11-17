// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: timer.hpp
// Author: crdrisko
// Date: 11/11/2020-07:06:45
// Description: A simple timer class to measure the speed of algorithms

#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <iostream>
#include <string>

/******************************************
 * timer to print elapsed time
 ******************************************/

class Timer
{
private:
    std::chrono::steady_clock::time_point last;

public:
    Timer() : last {std::chrono::steady_clock::now()} {}

    void printDiff(const std::string& msg = "Timer diff: ")
    {
        auto now {std::chrono::steady_clock::now()};
        std::chrono::duration<double, std::milli> diff {now - last};
        std::cout << msg << diff.count() << "ms\n";
        last = std::chrono::steady_clock::now();
    }
};

#endif
