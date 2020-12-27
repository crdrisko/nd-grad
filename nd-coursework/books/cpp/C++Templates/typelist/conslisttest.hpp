// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: conslisttest.hpp
// Author: crdrisko
// Date: 10/02/2020-08:35:46
// Description: An example usage of the ConsList structure

#ifndef CONSLISTTEST_HPP
#define CONSLISTTEST_HPP

#include <iostream>
#include <type_traits>

#include "cons.hpp"
#include "insertionsort.hpp"

template<typename T, typename U>
struct SmallerThanT
{
    static constexpr bool value = sizeof(T) < sizeof(U);
};

void conslisttest()
{
    using ConsList = Cons<int, Cons<char, Cons<short, Cons<double>>>>;
    using SortedTypes = InsertionSort<ConsList, SmallerThanT>;
    using Expected = Cons<char, Cons<short, Cons<int, Cons<double>>>>;
    std::cout << std::is_same<SortedTypes, Expected>::value << '\n';
}

#endif
