// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: pushfront.hpp
// Author: crdrisko
// Date: 11/07/2020-08:04:37
// Description: A metafunction for inserting a new element at the front of a tuple

#ifndef PUSHFRONT_HPP
#define PUSHFRONT_HPP

#include "tuple.hpp"
#include "tupletypelist.hpp"

template<typename... Types, typename V>
PushFront<Tuple<Types...>, V> pushFront(Tuple<Types...> const& tuple, V const& value)
{
    return PushFront<Tuple<Types...>, V>(value, tuple);
}

#endif
