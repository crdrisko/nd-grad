// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: pushback.hpp
// Author: crdrisko
// Date: 11/07/2020-08:07:53
// Description: A metafunction for inserting a new element at the back of a tuple

#ifndef PUSHBACK_HPP
#define PUSHBACK_HPP

#include "tuple.hpp"
#include "tupletypelist.hpp"

// basis case
template<typename V>
Tuple<V> pushBack(Tuple<> const&, V const& value)
{
    return Tuple<V>(value);
}

// basis case
template<typename Head, typename... Tail, typename V>
Tuple<Head, Tail..., V> pushBack(Tuple<Head, Tail...> const& tuple, V const& value)
{
    return Tuple<Head, Tail..., V>(tuple.getHead(), pushBack(tuple.getTail(), value));
}

#endif
