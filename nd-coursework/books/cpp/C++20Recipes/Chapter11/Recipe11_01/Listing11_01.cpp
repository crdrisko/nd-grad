// Copyright (c) 2020 J. Burton Browning and Bruce Sutherland. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing11_01.cpp
// Author: crdrisko
// Date: 10/13/2020-07:15:04
// Description: The std::thread::hardware_concurrency method

#include <iostream>
#include <thread>

int main()
{
    const unsigned int numberOfProcessors {std::thread::hardware_concurrency()};

    std::cout << "This system can run " << numberOfProcessors << " concurrent tasks" << std::endl;

    return 0;
}
