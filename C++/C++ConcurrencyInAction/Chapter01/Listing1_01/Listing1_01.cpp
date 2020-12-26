// Copyright (c) 2019 by Anthony Williams. All rights reserved.
// Licensed under the Boost Software License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_01.cpp
// Author: crdrisko
// Date: 12/25/2020-10:27:23
// Description: A simple Hello Concurrent World program

#include <iostream>
#include <thread>

void hello() { std::cout << "Hello Concurrent World\n"; }

int main()
{
    std::thread t(hello);
    t.join();
}
