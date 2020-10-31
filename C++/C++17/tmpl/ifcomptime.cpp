// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: ifcomptime.cpp
// Author: crdrisko
// Date: 10/29/2020-07:15:01
// Description: Demonstrating how the compile-time if statement works

#include "ifcomptime.hpp"

#include <iostream>
#include <string>

int main()
{
    std::cout << asString(42) << '\n';
    std::cout << asString(std::string("hello")) << '\n';
    std::cout << asString("hello") << '\n';
}
