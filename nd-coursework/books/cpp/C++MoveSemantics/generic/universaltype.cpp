// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: universaltype.cpp
// Author: crdrisko
// Date: 08/17/2021-08:37:33
// Description: Using universal references of specific types

#include <iostream>
#include <string>
#include <string_view>

// require a universal reference of a specific type:
// - no implicit type conversions supported
template<typename T>
requires std::is_same_v<std::remove_cvref_t<T>, std::string> void requiresSame(T&&)
{
    // ...
}

// require a universal reference of a specific type:
// - implicit but no explicit type conversions supported
template<typename T>
requires std::is_convertible_v<T, std::string> void requireConvertible(T&&)
{
    // ...
}

// require a universal reference of a specific type:
// - even explicit type conversions supported
// note: the order of arguments differs
template<typename T>
requires std::is_constructible_v<std::string, T> void requireConstructible(T&&)
{
    // ...
}

int main()
{
    std::string s       = "hi";
    std::string_view sv = "hi";

    requiresSame(s);   // OK
    // requiresSame(sv);     // ERROR: no std::string
    // requiresSame("hi");   // ERROR: no std::string

    requireConvertible(s);   // OK
    // requireConvertible(sv);     // ERROR: not implicit converversion to std::string
    requireConvertible("hi");   // OK

    requireConstructible(s);      // OK
    requireConstructible(sv);     // OK (explicit conversion used)
    requireConstructible("hi");   // OK
}
