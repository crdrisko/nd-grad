// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: largesttypeacc.hpp
// Author: crdrisko
// Date: 09/30/2020-08:18:46
// Description: A more generic metafunction that accumulates all elements of a typelist into the largest type

#ifndef LARGESTTYPEACC_HPP
#define LARGESTTYPEACC_HPP

#include "../traits/ifthenelse.hpp"
#include "accumulate.hpp"
#include "typelistfront.hpp"
#include "typelistisempty.hpp"
#include "typelistpopfront.hpp"

template<typename T, typename U>
class LargerTypeT : public IfThenElseT<sizeof(T) >= sizeof(U), T, U>
{
};

template<typename Typelist, bool Empty = IsEmpty<Typelist>::value>
class LargestTypeAccT;

template<typename Typelist>
class LargestTypeAccT<Typelist, false> : public AccumulateT<PopFront<Typelist>, LargerTypeT, Front<Typelist>>
{
};

template<typename Typelist>
class LargestTypeAccT<Typelist, true>
{
};

template<typename Typelist>
using LargestTypeAcc = typename LargestTypeAccT<Typelist>::Type;

#endif
