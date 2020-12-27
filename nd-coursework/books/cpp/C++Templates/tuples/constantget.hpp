// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: constantget.hpp
// Author: crdrisko
// Date: 12/05/2020-08:16:00
// Description: An improved implementation of get that operates in constant time

#ifndef CONSTANTGET_HPP
#define CONSTANTGET_HPP

#include "tupleelt1.hpp"

template<unsigned H, typename T>
T& getHeight(TupleElt<H, T>& te)
{
    return te.get();
}

template<typename... Types>
class Tuple;

template<unsigned I, typename... Elements>
auto get(Tuple<Elements...>& t) -> decltype(getHeight<sizeof...(Elements) - I - 1>(t))
{
    return getHeight<sizeof...(Elements) - I - 1>(t);
}

#endif
