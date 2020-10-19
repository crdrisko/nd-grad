// Copyright (c) 2020 J. Burton Browning and Bruce Sutherland. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing11_03.cpp
// Author: crdrisko
// Date: 10/13/2020-07:23:36
// Description: Forgetting to call join() on a thread

#include <iostream>
#include <thread>

void ThreadTask()
{
    for (unsigned int i {0}; i < 20; ++i)
        std::cout << "Output from thread" << std::endl;
}

int main(int argc, char* argv[])
{
    const unsigned int numberOfProcessors {std::thread::hardware_concurrency()};

    std::cout << "This system can run " << numberOfProcessors << " concurrent tasks" << std::endl;

    if (numberOfProcessors > 1)
    {
        std::thread myThread {ThreadTask};
        std::cout << "Output from main" << std::endl;
    }
    else
        std::cout << "CPU does not have multiple cores." << std::endl;

    return 0;
}
