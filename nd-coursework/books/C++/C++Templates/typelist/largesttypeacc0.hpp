// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: largesttypeacc0.hpp
// Author: crdrisko
// Date: 09/30/2020-08:12:11
// Description: A metafunction that accumulates all elements of a typelist into the largest type

#ifndef LARGESTTYPEACC0_HPP
#define LARGESTTYPEACC0_HPP

#include "accumulate.hpp"
#include "typelistfront.hpp"
#include "typelistpopfront.hpp"
#include "../traits/ifthenelse.hpp"

template<typename T, typename U>
class LargerTypeT : public IfThenElseT<sizeof(T) >= sizeof(U), T, U> {};

template<typename Typelist>
class LargestTypeAccT : public AccumulateT<PopFront<Typelist>, LargerTypeT, Front<Typelist>> {};

template<typename Typelist>
using LargestTypeAcc = typename LargestTypeAccT<Typelist>::Type;

#endif
