// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: select.hpp
// Author: crdrisko
// Date: 11/21/2020-06:40:04
// Description: An algorithm for making a new tuple out of the supplied ordering passed as an index list

#ifndef SELECT_HPP
#define SELECT_HPP

#include "makeindexlist.hpp"
#include "maketuple.hpp"
#include "tuple.hpp"
#include "tupleget.hpp"

template<typename... Elements, unsigned... Indices>
auto select(Tuple<Elements...> const& t, Valuelist<unsigned, Indices...>)
{
    return makeTuple(get<Indices>(t)...);
}

#endif
