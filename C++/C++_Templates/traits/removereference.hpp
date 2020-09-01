// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: removereference.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/18/2020-12:46:29
// Description: A trait for removing references from a template parameter, based off std::remove_reference<>

#ifndef REMOVEREFERENCE_HPP
#define REMOVEREFERENCE_HPP

template<typename T>
struct RemoveReferenceT
{
    using Type = T;
};

template<typename T>
struct RemoveReferenceT<T&>
{
    using Type = T;
};

template<typename T>
struct RemoveReferenceT<T&&>
{
    using Type = T;
};

#endif
