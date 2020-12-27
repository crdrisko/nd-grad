// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: rparam.hpp
// Author: crdrisko
// Date: 09/01/2020-10:01:22
// Description: A policy trait for a read-only parameter type

#ifndef RPARAM_HPP
#define RPARAM_HPP

#include <type_traits>

#include "ifthenelse.hpp"

template<typename T>
struct RParam
{
    using Type = IfThenElse<(sizeof(T) <= 2 * sizeof(void*)
                             && std::is_trivially_copy_constructible<T>::value
                             && std::is_trivially_move_constructible<T>::value),
                            T,
                            T const&>;
};

#endif
