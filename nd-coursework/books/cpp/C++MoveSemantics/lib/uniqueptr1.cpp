// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: uniqueptr1.cpp
// Author: crdrisko
// Date: 08/29/2021-08:53:31
// Description: Demonstrating how to use move semantics with std::unique_ptr

#include <iostream>
#include <memory>
#include <string>

std::unique_ptr<std::string> source()
{
    static long id {0};

    // create string with new and let ptr own it:
    auto ptr = std::make_unique<std::string>("obj" + std::to_string(++id));

    // ...

    return ptr;   // transfer ownership to caller
}

int main()
{
    std::unique_ptr<std::string> p;
    for (int i = 0; i < 10; ++i)
    {
        p = source();   // p gets ownership of the returned object

        std::cout << *p << '\n';

        // ...
    }
}   // last-owned object of p is deleted
