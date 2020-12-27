// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: ctvalue.hpp
// Author: crdrisko
// Date: 12/05/2020-08:24:18
// Description: A value that can be used at compile-time

#ifndef CTVALUE_HPP
#define CTVALUE_HPP

template<typename T, T Value>
struct CTValue
{
    static constexpr T value = Value;
};

#endif
