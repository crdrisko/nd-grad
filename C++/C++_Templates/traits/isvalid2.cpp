// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isvalid2.cpp
// Author: crdrisko
// Date: 08/31/2020-13:15:42
// Description: Again using the isValid traits factory to define a number of traits checking if certain members exist

#include <iostream>
#include <string>
#include <utility>

#include "isvalid.hpp"

// define to check for data member first:
constexpr auto hasFirst
    = isValid([](auto&& x) -> decltype((void)&x.first) {});

template<typename T>
using HasFirstT = decltype(hasFirst(std::declval<T>()));


// define to check for member type size_type:
constexpr auto hasSizeType
    = isValid([](auto&& x) -> typename std::decay_t<decltype(x)>::size_type {});

template<typename T>
using HasSizeTypeT = decltype(hasSizeType(std::declval<T>()));


// define to check for <:
constexpr auto hasLess
    = isValid([](auto&& x, auto&& y) -> decltype(x < y) {});

template<typename T1, typename T2>
using HasLessT = decltype(hasLess(std::declval<T1>(), std::declval<T2>()));

int main()
{
    std::cout << std::boolalpha;

    std::cout << "first: " << HasFirstT<std::pair<int, int>>::value << '\n';    // yields true

    struct CX
    {
        using size_type = std::size_t;
    };

    std::cout << "size_type: " << HasSizeTypeT<CX>::value << '\n';              // yields true
    std::cout << "size_type: " << HasSizeTypeT<int>::value << '\n';             // yields false

    std::cout << HasLessT<int, char>::value << '\n';                            // yields true
    std::cout << HasLessT<std::string, std::string>::value << '\n';             // yields true
    std::cout << HasLessT<std::string, int>::value << '\n';                     // yields false
    std::cout << HasLessT<std::string, char*>::value << '\n';                   // yields true
}
