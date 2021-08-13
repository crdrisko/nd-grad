// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: movenoexcept.cpp
// Author: crdrisko
// Date: 08/12/2021-10:32:32
// Description: A program to demonstrate whether declaring move constructors with noexcept is worth it

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#define NOEXCEPT noexcept   // ~42 ms
// #define NOEXCEPT         // ~163 ms

// string wrapper with move constructor:
struct Str
{
    std::string val;

    // ensure each string has 100 characters:
    Str() : val(100, 'a') {}   // don't use braces here

    // enable copying:
    Str(const Str&) = default;

    // enable moving (with and without noexcept):
    Str(Str&& s) NOEXCEPT : val {std::move(s.val)} {}
};

int main()
{
    // create vector of 1 Million wrapped strings:
    std::vector<Str> coll;
    coll.resize(1'000'000);

    // measure time to reallocate memory for all elements:
    auto t0 = std::chrono::steady_clock::now();
    coll.reserve(coll.capacity() + 1);
    auto t1 = std::chrono::steady_clock::now();

    std::chrono::duration<double, std::milli> d {t1 - t0};
    std::cout << d.count() << "ms\n";
}
