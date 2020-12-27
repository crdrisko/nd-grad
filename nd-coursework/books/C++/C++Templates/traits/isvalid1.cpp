// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isvalid1.cpp
// Author: crdrisko
// Date: 08/31/2020-11:07:05
// Description: Using the isValid traits factory to define a number of traits checking if certain members exist

#include <iostream>
#include <string>
#include <utility>

#include "isvalid.hpp"

int main()
{
    std::cout << std::boolalpha;

    // define to check for data member first:
    constexpr auto hasFirst
        = isValid([](auto x) -> decltype((void)valueT(x).first) {});

    std::cout << "hasFirst: " << hasFirst(type<std::pair<int, int>>) << '\n';   // yields true

    // define to check for member type size_type:
    constexpr auto hasSizeType
        = isValid([](auto x) -> typename decltype(valueT(x))::size_type {});

    struct CX
    {
        using size_type = std::size_t;
    };

    std::cout << "hasSizeType: " << hasSizeType(type<CX>) << '\n';              // yields true

    if constexpr(!hasSizeType(type<int>))
        std::cout << "int has no size_type\n";

    // define to check for <:
    constexpr auto hasLess
        = isValid([](auto x, auto y) -> decltype(valueT(x) < valueT(y)) {});

    std::cout << hasLess(42, type<char>) << '\n';                               // yields false??
    std::cout << hasLess(type<std::string>, type<std::string>) << '\n';         // yields true
    std::cout << hasLess(type<std::string>, type<int>) << '\n';                 // yields false
    std::cout << hasLess(type<std::string>, "hello") << '\n';                   // yields false??
}
