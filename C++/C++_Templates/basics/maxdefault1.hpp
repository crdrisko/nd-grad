// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: maxdefault1.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/26/2020-07:55:15
// Description: Using the operator?: to set a default return type (C++14 and on)

#ifndef MAXDEFAULT1_HPP
#define MAXDEFAULT1_HPP

#include <type_traits>

template<typename T1, typename T2,
         typename RT = std::decay_t<decltype(true ? T1() : T2())>>
RT max(T1 a, T2 b)
{
    return b < a ? a : b;
}

#endif
