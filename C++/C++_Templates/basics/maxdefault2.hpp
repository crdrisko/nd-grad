// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: maxdefault2.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/26/2020-08:00:21
// Description: Using std::common_type<> to specify the default value for the return type (C++14 and on)

#ifndef MAXDEFAULT2_HPP
#define MAXDEFAULT2_HPP

#include <type_traits>

template<typename T1, typename T2,
         typename RT = std::common_type_t<T1, T2>>
RT max(T1 a, T2 b)
{
    return b < a ? a : b;
}

#endif
