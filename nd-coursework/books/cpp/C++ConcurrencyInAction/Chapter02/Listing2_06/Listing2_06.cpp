// Copyright (c) 2019 by Anthony Williams. All rights reserved.
// Licensed under the Boost Software License. See the LICENSE file in the project root for more information.
//
// Name: Listing2_06.cpp
// Author: crdrisko
// Date: 12/26/2020-08:01:47
// Description: scoped_thread and example usage

#include <stdexcept>
#include <thread>
#include <utility>

class scoped_thread
{
    std::thread t;

public:
    explicit scoped_thread(std::thread t_) : t(std::move(t_))
    {
        if (!t.joinable())
            throw std::logic_error("No thread");
    }

    ~scoped_thread() { t.join(); }
    scoped_thread(scoped_thread const&)            = delete;
    scoped_thread& operator=(scoped_thread const&) = delete;
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
    scoped_thread t((std::thread(func(some_local_state))));

    do_something_in_current_thread();
}

int main() { f(); }
