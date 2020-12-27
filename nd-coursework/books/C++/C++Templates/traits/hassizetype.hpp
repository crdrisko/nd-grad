// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: hassizetype.hpp
// Author: crdrisko
// Date: 08/30/2020-18:16:28
// Description: A trait that can determine whether a given type T has a member type size_type

#ifndef HASSIZETYPE_HPP
#define HASSIZETYPE_HPP

#include <type_traits>                                      // defines true_type and false_type

// helper to ignore any number of template parameters:
template<typename...>
using VoidT = void;

// primary template:
template<typename, typename = VoidT<>>
struct HasSizeTypeT : std::false_type {};

// partial specialization (may be SFINAE'd away):
template<typename T>
struct HasSizeTypeT<T, VoidT<typename T::size_type>> : std::true_type {};

#endif
