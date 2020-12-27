// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: tupleget.hpp
// Author: crdrisko
// Date: 10/19/2020-10:05:01
// Description: The get function template which walks recursively through the structure to extract the requested element

#ifndef TUPLEGET_HPP
#define TUPLEGET_HPP

#include "tuple0.hpp"

// recursive case:
template<unsigned N>
struct TupleGet
{
    template<typename Head, typename... Tail>
    static auto apply(Tuple<Head, Tail...> const& t)
    {
        return TupleGet<N - 1>::apply(t.getTail());
    }
};

// basis case:
template<>
struct TupleGet<0>
{
    template<typename Head, typename... Tail>
    static Head const& apply(Tuple<Head, Tail...> const& t)
    {
        return t.getHead();
    }
};

template<unsigned N, typename... Types>
auto get(Tuple<Types...> const& t)
{
    return TupleGet<N>::apply(t);
}

#endif
