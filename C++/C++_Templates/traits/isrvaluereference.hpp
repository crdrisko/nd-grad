// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isrvaluereference.hpp - Version 1.0.0
// Author: crdrisko
// Date: 09/01/2020-07:48:08
// Description: Determining if a type is a rvalue reference, based on std::is_rvalue_reference<>

#ifndef ISRVALUEREFERENCE_HPP
#define ISRVALUEREFERENCE_HPP

#include <type_traits>

template<typename T>
struct IsRValueReferenceT : std::false_type {};             // by default no lvalue reference

template<typename T>
struct IsRValueReferenceT<T&&> : std::true_type             // unless T is rvalue references
{
    using BaseT = T;                                        // type referring to
};

#endif
