// Copyright (c) 2019 by Anthony Williams. All rights reserved.
// Licensed under the Boost Software License. See the LICENSE file in the project root for more information.
//
// Name: Listing2_03.cpp
// Author: crdrisko
// Date: 12/26/2020-07:43:06
// Description: Using RAII to wait for a thread to complete

#include <thread>

class thread_guard
{
    std::thread& t;

public:
    explicit thread_guard(std::thread& t_) : t(t_) {}

    ~thread_guard()
    {
        if (t.joinable())
            t.join();
    }
    thread_guard(thread_guard const&)            = delete;
    thread_guard& operator=(thread_guard const&) = delete;
};

void do_something(int& i) { ++i; }

struct func
{
    int& i;

    func(int& i_) : i(i_) {}

    void operator()()
    {
        for (unsigned j = 0; j < 1000000; ++j)
            do_something(i);
    }
};

void do_something_in_current_thread() {}

void f()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    thread_guard g(t);

    do_something_in_current_thread();
}

int main() { f(); }
