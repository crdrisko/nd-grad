// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: plus3.hpp
// Author: crdrisko
// Date: 08/29/2020-11:29:06
// Description: Determining the return type of the + operator based on whether or not the operator is defined for the types

#ifndef PLUS3_HPP
#define PLUS3_HPP

#include "hasplus.hpp"

// primary template, used when HasPlusT yields true:
template<typename T1, typename T2, bool = HasPlusT<T1, T2>::value>
struct PlusResultT
{
    using Type = decltype(std::declval<T1>() + std::declval<T2>());
};

// partial specialization, used otherwise:
template<typename T1, typename T2>
struct PlusResultT<T1, T2, false> {};

#endif
