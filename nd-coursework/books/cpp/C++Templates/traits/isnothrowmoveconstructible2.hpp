// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isnothrowmoveconstructible2.hpp
// Author: crdrisko
// Date: 08/31/2020-20:31:40
// Description: Making IsNothrowMoveConstructibleT SFINAE friendly, based on std::is_move_constructible<>

#ifndef ISNOTHROWMOVECONSTRUCTIBLE2_HPP
#define ISNOTHROWMOVECONSTRUCTIBLE2_HPP

#include <type_traits>                                      // for bool_constant
#include <utility>                                          // for declval

// primary template:
template<typename T, typename = std::void_t<>>
struct IsNothrowMoveConstructibleT : std::false_type {};

// partial specialization (may be SFINAE'd away):
template<typename T>
struct IsNothrowMoveConstructibleT<T, std::void_t<decltype(T(std::declval<T>()))>>
    : std::bool_constant<noexcept(T(std::declval<T>()))> {};

#endif
