// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: hasvarious.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/31/2020-08:16:27
// Description: Combining multible constraints into a trait using void_t

#ifndef HASVARIOUS_HPP
#define HASVARIOUS_HPP

#include <type_traits>                                      // for true_type, false_type, and void_t
#include <utility>                                          // for declval

// primary template:
template<typename, typename = std::void_t<>>
struct HasVariousT : std::false_type {};

// partial specialization (may be SFINAE'd away):
template<typename T>
struct HasVariousT<T, std::void_t<decltype(std::declval<T>().begin()),
                                  typename T::difference_type,
                                  typename T::iterator>> : std::true_type {};

#endif
