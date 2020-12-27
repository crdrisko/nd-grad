// Copyright (c) 2019 by Anthony Williams. All rights reserved.
// Licensed under the Boost Software License. See the LICENSE file in the project root for more information.
//
// Name: Listing2_08.cpp
// Author: crdrisko
// Date: 12/26/2020-08:24:00
// Description: Spawns some threads and waits for them to finish

#include <algorithm>
#include <functional>
#include <thread>
#include <vector>

void do_work(unsigned id) {}

void f1()
{
    std::vector<std::thread> threads;

    for (unsigned i = 0; i < 20; ++i)
        threads.emplace_back(do_work, i);                   // Spawns threads

    for (auto& entry : threads)                             // Calls join() on each thread in turn
        entry.join();
}

void f2()
{
    std::vector<std::thread> threads;

    for (unsigned i = 0; i < 20; ++i)
        threads.push_back(std::thread(do_work, i));         // Spawns threads

    std::for_each(threads.begin(), threads.end(),           // Calls join() on each thread in turn
        std::mem_fn(&std::thread::join));
}

int main()
{
    f1();
    f2();
}
