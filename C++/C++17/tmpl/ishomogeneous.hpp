// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: ishomogeneous.hpp
// Author: crdrisko
// Date: 10/30/2020-07:24:05
// Description: Using fold expressions to determine if a parameter pack consists of all the same types

#ifndef ISHOMOGENEOUS_HPP
#define ISHOMOGENEOUS_HPP

#include <type_traits>

// check whether passed types are homogeneous:
template<typename T1, typename... TN>
struct IsHomogeneous
{
    static constexpr bool value = (std::is_same_v<T1, TN> && ...);
};

// check whether passed arguments have the same type:
template<typename T1, typename... TN>
constexpr bool isHomogeneous(T1, TN...)
{
    return (std::is_same_v<T1, TN> && ...);
}


#endif
