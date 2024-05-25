// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isnothrowmoveconstructible1.hpp
// Author: crdrisko
// Date: 08/31/2020-20:31:33
// Description: Using the noexcept operator to implement a trait testing if an object is no-throw move constructible

#ifndef ISNOTHROWMOVECONSTRUCTIBLE1_HPP
#define ISNOTHROWMOVECONSTRUCTIBLE1_HPP

#include <type_traits>   // for bool_constant
#include <utility>       // for declval

template<typename T>
struct IsNothrowMoveConstructibleT : std::bool_constant<noexcept(T(std::declval<T>()))>
{
};

#endif
