// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: noexceptcalls.cpp
// Author: crdrisko
// Date: 09/29/2020-18:41:26
// Description: Demonstrating how in C++17, noexcept changes the type of a function

#include <iostream>

template<typename T>
void call(T op1, T op2)
{
    op1();
    op2();
}

void f1()
{
    std::cout << "f1()\n";
}

void f2() noexcept
{
    std::cout << "f2()\n";
}

int main()
{
    call(f1, f2);                                           // ERROR since C++17
}
