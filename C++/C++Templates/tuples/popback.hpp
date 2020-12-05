// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: popback.hpp
// Author: crdrisko
// Date: 11/07/2020-08:44:36
// Description: A metafunction for removing the last element from a tuple

#ifndef POPBACK_HPP
#define POPBACK_HPP

#include "../typelist/typelistpopback.hpp"
#include "popFront.hpp"
#include "reverse.hpp"
#include "tuple.hpp"

template<typename... Types>
PopBack<Tuple<Types...>> popBack(Tuple<Types...> const& tuple)
{
    return reverse(popFront(reverse(tuple)));
}

#endif
