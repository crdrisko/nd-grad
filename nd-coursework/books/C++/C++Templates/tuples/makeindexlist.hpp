// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: makeindexlist.hpp
// Author: crdrisko
// Date: 11/21/2020-06:29:12
// Description: Creating an index list for more efficient tuple reversals

#ifndef MAKEINDEXLIST_HPP
#define MAKEINDEXLIST_HPP

#include "../typelist/valuelist.hpp"

// recursive case
template<unsigned N, typename Result = Valuelist<unsigned>>
struct MakeIndexListT : MakeIndexListT<N - 1, PushFront<Result, CTValue<unsigned, N - 1>>>
{
};

// basis case
template<typename Result>
struct MakeIndexListT<0, Result>
{
    using Type = Result;
};

template<unsigned N>
using MakeIndexList = typename MakeIndexListT<N>::Type;

#endif
