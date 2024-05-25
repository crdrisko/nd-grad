// Copyright (c) 2019 by Anthony Williams. All rights reserved.
// Licensed under the Boost Software License. See the LICENSE file in the project root for more information.
//
// Name: Listing2_01.cpp
// Author: crdrisko
// Date: 12/25/2020-11:00:41
// Description: A function that returns while a thread still has access to local variables

#include <thread>

void do_something(int& i) { ++i; }

struct func
{
    int& i;

    func(int& i_) : i(i_) {}

    void operator()()
    {
        for (unsigned j = 0; j < 1000000; ++j)
            do_something(i);   // Potential access to dangling reference
    }
};

void oops()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();   // Don't wait for thread to finish
}   // New thread might still be running

int main() { oops(); }
