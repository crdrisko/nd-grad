// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: tryequals.hpp
// Author: cdrisko
// Date: 07/27/2020-16:38:16
// Description: Using the IsEqualityComparable to either envoke the operator== or throw an exception

#ifndef TRYEQUALS_HPP
#define TRYEQUALS_HPP

#include <exception>

#include "isequalitycomparable.hpp"

template<typename T,
         bool EqComparable = IsEqualityComparable<T>::value>
struct TryEquals
{
    static bool equals(T const& x1, T const& x2)
    {
        return x1 == x2;
    }
};

class NotEqualityComparable : public std::exception {};

template<typename T>
struct TryEquals<T, false>
{
    static bool equals(T const& x1, T const& x2)
    {
        throw NotEqualityComparable();
    }
};

#endif
