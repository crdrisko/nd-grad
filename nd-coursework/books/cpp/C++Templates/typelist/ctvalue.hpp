// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: ctvalue.hpp
// Author: crdrisko
// Date: 10/02/2020-07:55:48
// Description: A class template that represents a value of a specific type within a typelist, based on std::integral_constant<>

#ifndef CTVALUE_HPP
#define CTVALUE_HPP

template<typename T, T Value>
struct CTValue
{
    static constexpr T value = Value;
};

#endif
