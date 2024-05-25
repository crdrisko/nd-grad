// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: inlinethreadlocal.hpp
// Author: crdrisko
// Date: 09/29/2020-06:59:41
// Description: Demonstrating the use of thread_local with inline variables

#ifndef INLINETHREADLOCAL_HPP
#define INLINETHREADLOCAL_HPP

#include <iostream>
#include <string>

struct MyData
{
    inline static std::string gName              = "global";   // unique in program
    inline static thread_local std::string tName = "tls";      // unique per thread
    std::string lName                            = "local";    // for each object
    // ...
    void print(const std::string& msg) const
    {
        std::cout << msg << '\n';
        std::cout << "- gName: " << gName << '\n';
        std::cout << "- tName: " << tName << '\n';
        std::cout << "- lName: " << lName << '\n';
    }
};

inline thread_local MyData myThreadData;   // one object per thread

#endif
