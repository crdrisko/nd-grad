// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: islvaluereference.hpp - Version 1.0.0
// Author: crdrisko
// Date: 09/01/2020-07:48:02
// Description: Determining if a type is a lvalue reference, based on std::is_lvalue_reference<>

#ifndef ISLVALUEREFERENCE_HPP
#define ISLVALUEREFERENCE_HPP

#include <type_traits>

template<typename T>
struct IsLValueReferenceT : std::false_type {};             // by default no lvalue reference

template<typename T>
struct IsLValueReferenceT<T&> : std::true_type              // unless T is lvalue references
{
    using BaseT = T;                                        // type referring to
};

#endif
