// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: reverse.hpp
// Author: crdrisko
// Date: 11/07/2020-08:40:09
// Description: A metafunction for reversing a tuple

#ifndef REVERSE_HPP
#define REVERSE_HPP

#include "../typelist/typelistreverse.hpp"
#include "pushback.hpp"
#include "tuple.hpp"

// basis case
Tuple<> reverse(Tuple<> const& t) { return t; }

// recursive case
template<typename Head, typename... Tail>
Reverse<Tuple<Head, Tail...>> reverse(Tuple<Head, Tail...> const& t)
{
    return pushBack(reverse(t.getTail()), t.getHead());
}

#endif
