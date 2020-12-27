// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: plus1.hpp
// Author: crdrisko
// Date: 08/28/2020-22:01:29
// Description: Determining the type produced by adding values of two (possibly different) types with the + operator

#ifndef PLUS1_HPP
#define PLUS1_HPP

template<typename T1, typename T2>
struct PlusResultT
{
    using Type = decltype(T1() + T2());
};

template<typename T1, typename T2>
using PlusResult = typename PlusResultT<T1, T2>::Type;

#endif
