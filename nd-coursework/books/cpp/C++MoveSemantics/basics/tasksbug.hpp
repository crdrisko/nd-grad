// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: tasksbug.hpp
// Author: crdrisko
// Date: 08/08/2021-07:22:14
// Description: Enabling move semantics by generating the default implementation of the move operations for our Tasks class

#ifndef TASKSBUG_HPP
#define TASKSBUG_HPP

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

    // OOPS: enable default move semantics:
    Tasks(Tasks&&) = default;
    Tasks& operator=(Tasks&&) = default;

    // at the end wait for all started threads:
    ~Tasks()
    {
        for (int i = 0; i < numThreads; ++i)
            threads[i].join();
    }
};

#endif
