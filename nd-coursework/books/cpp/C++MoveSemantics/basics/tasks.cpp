// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: tasks.cpp
// Author: crdrisko
// Date: 08/08/2021-07:21:57
// Description: Starting multiple threads and waiting for their end

#include "tasks.hpp"

#include <chrono>
#include <iostream>

int main()
{
    Tasks ts;
    ts.start(
        []
        {
            std::this_thread::sleep_for(std::chrono::seconds {2});
            std::cout << "\nt1 done" << std::endl;
        });

    ts.start([] { std::cout << "\nt2 done" << std::endl; });
}
