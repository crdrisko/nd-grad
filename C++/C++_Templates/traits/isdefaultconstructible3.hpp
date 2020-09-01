// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isdefaultconstructible3.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/29/2020-09:21:41
// Description: Using partial specialization and SFINAE to implement our IsDefaultConstructableT<> template

#ifndef ISDEFAULTCONSTRUCTIBLE3_HPP
#define ISDEFAULTCONSTRUCTIBLE3_HPP

#include <type_traits>                                      // defines true_type and false_type

#include "issame.hpp"

// helper to ignore any number of template parameters:
template<typename...> using VoidT = void;

// primary template:
template<typename, typename = VoidT<>>
struct IsDefaultConstructibleT : std::false_type {};

// partial specialization (may be SFINAE'd away):
template<typename T>
struct IsDefaultConstructibleT<T, VoidT<decltype(T())>> : std::true_type {};

#endif
