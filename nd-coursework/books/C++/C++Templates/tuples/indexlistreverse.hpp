// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: indexlistreverse.hpp
// Author: crdrisko
// Date: 11/21/2020-06:34:49
// Description: Implementation of the reverse algorithm for tuples using index lists

#ifndef INDEXLISTREVERSE_HPP
#define INDEXLISTREVERSE_HPP

#include "makeindexlist.hpp"
#include "maketuple.hpp"
#include "tuple.hpp"
#include "tupleget.hpp"

template<typename... Elements, unsigned... Indices>
auto reverseImpl(Tuple<Elements...> const& t, Valuelist<unsigned, Indices...>)
{
    return makeTuple(get<Indices>(t)...);
}

template<typename... Elements>
auto reverse(Tuple<Elements...> const& t)
{
    return reverseImpl(t, Reverse<MakeIndexList<sizeof...(Elements)>>());
}

#endif
