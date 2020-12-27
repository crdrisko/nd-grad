// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: multiply.hpp
// Author: crdrisko
// Date: 10/02/2020-07:57:27
// Description: Computing the product of two compile-time values with the same type, producing a new compile-time value

#ifndef MULTIPLY_HPP
#define MULTIPLY_HPP

#include "ctvalue.hpp"

template<typename T, typename U>
struct MultiplyT;

template<typename T, T Value1, T Value2>
struct MultiplyT<CTValue<T, Value1>, CTValue<T, Value2>>
{
public:
    using Type = CTValue<T, Value1 * Value2>;
};

template<typename T, typename U>
using Multiply = typename MultiplyT<T, U>::Type;

#endif
