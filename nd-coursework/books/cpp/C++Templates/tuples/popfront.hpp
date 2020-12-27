// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: popfront.hpp
// Author: crdrisko
// Date: 11/07/2020-08:34:30
// Description: A metafunction for removing the first element from a tuple

#ifndef POPFRONT_HPP
#define POPFRONT_HPP

#include "tuple.hpp"
#include "tupletypelist.hpp"

template<typename... Types>
PopFront<Tuple<Types...>> popFront(Tuple<Types...> const& tuple)
{
    return tuple.getTail();
}

#endif
