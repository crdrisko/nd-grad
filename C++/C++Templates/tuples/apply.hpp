// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: apply.hpp
// Author: crdrisko
// Date: 12/05/2020-07:22:44
// Description: A simple function which applies a given function to each element of a tuple

#ifndef APPLY_HPP
#define APPLY_HPP

#include "../typelist/valuelist.hpp"
#include "makeindexlist.hpp"
#include "tuple.hpp"
#include "tupleget.hpp"

template<typename F, typename... Elements, unsigned... Indices>
auto applyImpl(F f, Tuple<Elements...> const& t, Valuelist<unsigned, Indices...>) -> decltype(f(get<Indices>(t)...))
{
    return f(get<Indices>(t)...);
}

template<typename F, typename... Elements, unsigned N = sizeof...(Elements)>
auto apply(F f, Tuple<Elements...> const& t) -> decltype(applyImpl(f, t, MakeIndexList<N>()))
{
    return applyImpl(f, t, MakeIndexList<N>());
}

#endif
