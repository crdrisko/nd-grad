// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: factory.cpp
// Author: crdrisko
// Date: 09/29/2020-18:16:49
// Description: Using our factory function to create even a type such as std::atomic<>

#include <memory>
#include <thread>

#include "factory.hpp"

int main()
{
    int i = create<int>(42);
    std::unique_ptr<int> up = create<std::unique_ptr<int>>(new int{42});
    std::atomic<int> ai = create<std::atomic<int>>(42);
}
