// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: decltypeauto.cpp
// Author: crdrisko
// Date: 10/31/2020-15:35:10
// Description: Demonstrating some of the "surprising" behavior when using decltype(auto) as a template parameter

#include <iostream>

template<decltype(auto) N>
struct S
{
    void printN() const { std::cout << "N: " << N << '\n'; }
};

static const int c = 42;
static int v       = 42;

int main()
{
    S<c> s1;     // deduces N as const int 42
    S<(c)> s2;   // deduces N as const int& referring to c
    s1.printN();
    s2.printN();

    S<(v)> s3;   // deduces N as int& referring to v
    v = 77;
    s3.printN();   // prints: N: 77
}
