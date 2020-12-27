// Copyright (c) 2019 by Anthony Williams. All rights reserved.
// Licensed under the Boost Software License. See the LICENSE file in the project root for more information.
//
// Name: Listing2_02.cpp
// Author: crdrisko
// Date: 12/26/2020-07:35:26
// Description: Waiting for a thread to finish

#include <thread>

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

    try
    {
        do_something_in_current_thread();
    }
    catch (...)
    {
        t.join();
        throw;
    }
    t.join();
}

int main()
{
    f();
}
