// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: ispointer.hpp
// Author: crdrisko
// Date: 09/01/2020-07:42:56
// Description: Determining if a type is a pointer, based on std::is_pointer<>

#ifndef ISPOINTER_HPP
#define ISPOINTER_HPP

#include <type_traits>

// primary template: by default not a pointer
template<typename T>
struct IsPointerT : std::false_type
{
};

// partial specialization for pointers
template<typename T>
struct IsPointerT<T*> : std::true_type
{
    using BaseT = T;   // type pointing to
};

#endif
