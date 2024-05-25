// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: ifcomptime.hpp
// Author: crdrisko
// Date: 10/29/2020-07:10:28
// Description: Using a compile-time if statement to convert a type to a string

#ifndef IFCOMPTIME_HPP
#define IFCOMPTIME_HPP

#include <string>
#include <type_traits>

template<typename T>
std::string asString(T x)
{
    if constexpr (std::is_same_v<T, std::string>)
        return x;   // statement invalid if no conversion to string

    else if constexpr (std::is_arithmetic_v<T>)
        return std::to_string(x);   // statement invalid if x is not numeric

    else
        return std::string(x);   // statement invalid if no conversion to string
}

#endif
