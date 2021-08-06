// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: initmeasure.hpp
// Author: crdrisko
// Date: 08/05/2021-07:58:03
// Description: A full function to measure the different approaches to initializing a Person class

#ifndef INITMEASURE_HPP
#define INITMEASURE_HPP

#include <chrono>
#include <string>

#ifdef USE_ALL
    #include "initall.hpp"
#else
    #ifdef USE_MOVE
        #include "initmove.hpp"
    #else
        #include "initclassic.hpp"
    #endif
#endif

// measure num initializations of whatever is currently defined as Person:
std::chrono::nanoseconds measure(int num)
{
    std::chrono::nanoseconds totalDur {0};

    for (int i = 0; i < num; ++i)
    {
        std::string fname = "a firstname a bit too long for SSO";
        std::string lname = "a lastname a bit too long for SSO";

        // measure how long it takes to create 3 Persons in different ways:
        auto t0 = std::chrono::steady_clock::now();
        Person p1 {"a firstname a bit too long for SSO", "a lastname a bit too long for SSO"};
        Person p2 {fname, lname};
        Person p3 {std::move(fname), std::move(lname)};
        auto t1 = std::chrono::steady_clock::now();

        totalDur += t1 - t0;
    }

    return totalDur;
}

#endif
