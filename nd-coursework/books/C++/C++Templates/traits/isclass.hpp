// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isclass.hpp
// Author: crdrisko
// Date: 09/01/2020-09:37:17
// Description: Determining if a type is a class, based on std::is_class<>

#ifndef ISCLASS_HPP
#define ISCLASS_HPP

#include <type_traits>

// primary template: by default no class
template<typename T, typename = std::void_t<>>
struct IsClassT : std::false_type {};

template<typename T>
struct IsClassT<T, std::void_t<int T::*>> : std::true_type {};                  // classes can have pointer-to-member

#endif
