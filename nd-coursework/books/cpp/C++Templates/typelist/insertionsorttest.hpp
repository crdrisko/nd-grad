// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: insertionsorttest.hpp
// Author: crdrisko
// Date: 10/02/2020-07:40:45
// Description: A simple test for verifying our insertion sort algorithm works as expected for Typelists

#ifndef INSERTIONSORTTEST_HPP
#define INSERTIONSORTTEST_HPP

#include <iostream>
#include <type_traits>

#include "insertionsort.hpp"
#include "typelist.hpp"

template<typename T, typename U>
struct SmallerThanT
{
    static constexpr bool value = sizeof(T) < sizeof(U);
};

void testInsertionSort()
{
    using Types = Typelist<int, char, short, double>;
    using ST = InsertionSort<Types, SmallerThanT>;

    std::cout << std::is_same<ST, Typelist<char, short, int, double>>::value << '\n';
}

#endif
