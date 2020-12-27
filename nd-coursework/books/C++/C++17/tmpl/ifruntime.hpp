// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: ifruntime.hpp
// Author: crdrisko
// Date: 10/29/2020-07:17:41
// Description: Using a regular, run-time if statement to convert a type to a string

#ifndef IFRUNTIME_HPP
#define IFRUNTIME_HPP

#include <string>
#include <type_traits>

template<typename T>
std::string asString(T x)
{
    if (std::is_same_v<T, std::string>)
        return x;                                           // ERROR if no conversion to string

    else if (std::is_numeric_v<T>)
        return std::to_string(x);                           // ERROR if x is not numeric

    else
        return std::string(x);                              // ERROR if no conversion to string
}

#endif
