// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: tupleeq.hpp
// Author: crdrisko
// Date: 10/20/2020-07:21:55
// Description: A definition of operator=() for our tuple class that compares two definitions element-wise

#ifndef TUPLEEQ_HPP
#define TUPLEEQ_HPP

#include <type_traits>

#include "tuple.hpp"

// basis case:
bool operator==(Tuple<> const&, Tuple<> const&)
{
    // empty tuples are always equivalent
    return true;
}

// recursive case:
template<typename Head1, typename... Tail1,
         typename Head2, typename... Tail2,
         typename = std::enable_if_t<sizeof...(Tail1) == sizeof...(Tail2)>>
bool operator==(Tuple<Head1, Tail1...> const& lhs, Tuple<Head2, Tail2...> const& rhs)
{
    return lhs.getHead() == rhs.getHead() && lhs.getTail() == rhs.getTail();
}

#endif
