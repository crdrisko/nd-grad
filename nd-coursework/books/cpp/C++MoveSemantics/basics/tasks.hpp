// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: tasks.hpp
// Author: crdrisko
// Date: 08/08/2021-07:21:52
// Description: Using a fixed-size array of a variable number of thread objects for which we explicitly call join() in the destructor to wait for their end

#ifndef TASKS_HPP
#define TASKS_HPP

#include <array>
#include <thread>

class Tasks
{
private:
    std::array<std::thread, 10> threads;   // array of threads for up to 10 tasks
    int numThreads {0};                    // current number of threads/tasks

public:
    Tasks() = default;

    // pass a new thread:
    template<typename T>
    void start(T op)
    {
        threads[numThreads] = std::thread {std::move(op)};
        ++numThreads;
    }

    // ...

    // at the end wait for all started threads:
    ~Tasks()
    {
        for (int i = 0; i < numThreads; ++i)
            threads[i].join();
    }
};

#endif
