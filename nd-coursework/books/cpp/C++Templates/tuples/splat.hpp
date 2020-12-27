// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: splat.hpp
// Author: crdrisko
// Date: 11/22/2020-06:45:29
// Description: An algorithm for selecting and repeating a single element from a tuple

#ifndef SPLAT_HPP
#define SPLAT_HPP

#include "../typelist/valuelist.hpp"
#include "select.hpp"
#include "tuple.hpp"

template<unsigned I, unsigned N, typename IndexList = Valuelist<unsigned>>
class ReplicatedIndexListT;

template<unsigned I, unsigned N, unsigned... Indices>
class ReplicatedIndexListT<I, N, Valuelist<unsigned, Indices...>>
    : public ReplicatedIndexListT<I, N - 1, Valuelist<unsigned, Indices..., I>>
{
};

template<unsigned I, unsigned... Indices>
class ReplicatedIndexListT<I, 0, Valuelist<unsigned, Indices...>>
{
public:
    using Type = Valuelist<unsigned, Indices...>;
};

template<unsigned I, unsigned N>
using ReplicatedIndexList = typename ReplicatedIndexListT<I, N>::Type;

template<unsigned I, unsigned N, typename... Elements>
auto splat(Tuple<Elements...> const& t)
{
    return select(t, ReplicatedIndexList<I, N>());
}

#endif
