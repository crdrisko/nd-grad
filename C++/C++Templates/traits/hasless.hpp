// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: hasless.hpp
// Author: crdrisko
// Date: 08/31/2020-08:10:54
// Description: Determining if a type has an overloaded < operator

#ifndef HASLESS_HPP
#define HASLESS_HPP

#include <type_traits>                                      // for true_type, false_type, and void_t
#include <utility>                                          // for declval

// primary template:
template<typename, typename, typename = std::void_t<>>
struct HasLessT : std::false_type {};

// partial specialization (may be SFINAE'd away):
template<typename T1, typename T2>
struct HasLessT<T1, T2, std::void_t<decltype(std::declval<T1>() < std::declval<T2>())>> : std::true_type {};

#endif
