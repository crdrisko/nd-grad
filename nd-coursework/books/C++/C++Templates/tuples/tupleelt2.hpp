// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: tupleelt2.hpp
// Author: crdrisko
// Date: 12/05/2020-08:05:13
// Description: Improving the storage of a tuple element if it is a class type and not marked final

#ifndef TUPLEELT2_HPP
#define TUPLEELT2_HPP

#include <type_traits>
#include <utility>

template<unsigned Height, typename T, bool = std::is_class<T>::value && !std::is_final<T>::value>
class TupleElt;

template<unsigned Height, typename T>
class TupleElt<Height, T, false>
{
    T value;

public:
    TupleElt() = default;

    template<typename U>
    TupleElt(U&& other) : value(std::forward<U>(other))
    {
    }

    T& get() { return value; }
    T const& get() const { return value; }
};

template<unsigned Height, typename T>
class TupleElt<Height, T, true> : private T
{
public:
    TupleElt() = default;

    template<typename U>
    TupleElt(U&& other) : T(std::forward<U>(other))
    {
    }

    T& get() { return *this; }
    T const& get() const { return *this; }
};

#endif
