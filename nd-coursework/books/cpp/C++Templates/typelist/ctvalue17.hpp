// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: ctvalue17.hpp
// Author: crdrisko
// Date: 10/02/2020-08:21:02
// Description: Using a single, deducible non-type parameter to define our CTValue type (C++17 and on)

#ifndef CTVALUE17_HPP
#define CTVALUE17_HPP

template<auto Value>
struct CTValue
{
    static constexpr auto value = Value;
};

#endif
