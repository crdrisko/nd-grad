// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: tupleelt1.hpp
// Author: crdrisko
// Date: 12/05/2020-07:54:46
// Description: An alternative to storing the current tuple element to avoid clashes between elements of the same type

#ifndef TUPLEELT1_HPP
#define TUPLEELT1_HPP

#include <utility>

template<unsigned Height, typename T>
class TupleElt
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

#endif
