// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: future.cpp
// Author: crdrisko
// Date: 08/29/2021-09:02:19
// Description: Demonstrating the use of move semantics with multithreading applications using futures, promises, and packaged tasks

#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

void getValue(std::promise<std::string> p)
{
    try
    {
        std::string ret {"vote"};

        // ...

        // store result:
        p.set_value_at_thread_exit(std::move(ret));
    }
    catch (...)
    {
        // store exception:
        p.set_exception_at_thread_exit(std::current_exception());
    }
}

int main()
{
    std::vector<std::future<std::string>> results;

    // create promise and future to deal with outcome of the thread started:
    std::promise<std::string> p;
    std::future<std::string> f {p.get_future()};
    results.push_back(std::move(f));

    // start thread and move the promise to it:
    std::thread t {getValue, std::move(p)};
    t.detach();   // would not be necessary for std::jthread

    // ...

    // wait for all threads to end:
    for (auto& fut : results)
        std::cout << fut.get() << '\n';
}
