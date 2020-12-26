// Copyright (c) 2019 by Anthony Williams. All rights reserved.
// Licensed under the Boost Software License. See the LICENSE file in the project root for more information.
//
// Name: Listing2_05.cpp
// Author: crdrisko
// Date: 12/26/2020-07:57:22
// Description: Returning a std::thread from a function

#include <thread>

void some_function() {}
void some_other_function(int) {}

std::thread f()
{
    void some_function();
    return std::thread(some_function);
}

std::thread g()
{
    void some_other_function(int);
    std::thread t(some_other_function, 42);
    return t;
}

int main()
{
    std::thread t1 = f();
    t1.join();

    std::thread t2 = g();
    t2.join();
}
