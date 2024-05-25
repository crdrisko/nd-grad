// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: tasksbug.cpp
// Author: crdrisko
// Date: 08/08/2021-07:22:18
// Description: Creating an invalid Tasks state using the default generated move operations

#include "tasksbug.hpp"

#include <chrono>
#include <exception>
#include <iostream>

int main()
{
    try
    {
        Tasks ts;
        ts.start(
            []
            {
                std::this_thread::sleep_for(std::chrono::seconds {2});
                std::cout << "\nt1 done" << std::endl;
            });

        ts.start([] { std::cout << "\nt2 done" << std::endl; });

        // OOPS: move tasks:
        Tasks other {std::move(ts)};
    }
    catch (const std::exception& e)
    {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    }
}
