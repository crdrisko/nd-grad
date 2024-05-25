// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: hasplus.hpp
// Author: crdrisko
// Date: 08/29/2020-11:21:21
// Description: A SFINAE-fiendly way to determine if the result of the + operator is valid for two types

#ifndef HASPLUS_HPP
#define HASPLUS_HPP

#include <type_traits>   // for true_type, false_type, and void_t
#include <utility>       // for declval

// primary template:
template<typename, typename, typename = std::void_t<>>
struct HasPlusT : std::false_type
{
};

// partial specialization (may be SFINAE'd away):
template<typename T1, typename T2>
struct HasPlusT<T1, T2, std::void_t<decltype(std::declval<T1>() + std::declval<T2>())>> : std::true_type
{
};

#endif
