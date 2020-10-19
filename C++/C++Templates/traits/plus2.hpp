// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: plus2.hpp
// Author: crdrisko
// Date: 08/28/2020-22:16:54
// Description: Determining the type produced by adding values of two (possibly different) types using std::declval<>

#ifndef PLUS2_HPP
#define PLUS2_HPP

#include <utility>

template<typename T1, typename T2>
struct PlusResultT
{
    using Type = decltype(std::declval<T1>() + std::declval<T2>());
};

template<typename T1, typename T2>
using PlusResult = typename PlusResultT<T1, T2>::Type;

#endif
