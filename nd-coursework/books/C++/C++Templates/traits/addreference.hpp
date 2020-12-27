// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: addreference.hpp
// Author: crdrisko
// Date: 08/18/2020-12:54:42
// Description: A trait for adding references to a template parameter, based off std::add_lvalue_reference<> and std::add_rvalue_reference<>

#ifndef ADDREFERENCE_HPP
#define ADDREFERENCE_HPP

template<typename T>
struct AddLValueReferenceT
{
    using Type = T&;
};

template<typename T>
using AddLValueReference = typename AddLValueReferenceT<T>::Type;

template<typename T>
struct AddRValueReferenceT
{
    using Type = T&&;
};

template<typename T>
using AddRValueReference = typename AddRValueReferenceT<T>::Type;

#endif
