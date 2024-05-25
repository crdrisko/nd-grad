// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: valuelisttest.hpp
// Author: crdrisko
// Date: 10/02/2020-08:20:53
// Description: A simple test for verifying our insertion sort algorithm works as expected for Valuelists

#ifndef VALUELISTTEST_HPP
#define VALUELISTTEST_HPP

#include <type_traits>

#include "ctvalue.hpp"
#include "insertionsort.hpp"
#include "valuelist.hpp"

template<typename T, typename U>
struct GreaterThanT;

template<typename T, T First, T Second>
struct GreaterThanT<CTValue<T, First>, CTValue<T, Second>>
{
    static constexpr bool value = First > Second;
};

void valuelisttest()
{
    using Integers       = Valuelist<int, 6, 2, 4, 9, 5, 2, 1, 7>;
    using SortedIntegers = InsertionSort<Integers, GreaterThanT>;

    static_assert(std::is_same_v<SortedIntegers, Valuelist<int, 9, 7, 6, 5, 4, 2, 2, 1>>, "insertion sort failed");
}

#endif
