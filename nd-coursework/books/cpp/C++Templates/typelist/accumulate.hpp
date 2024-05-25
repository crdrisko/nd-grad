// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: accumulate.hpp
// Author: crdrisko
// Date: 09/30/2020-07:33:22
// Description: A metafunction that combines all elements of a typelist into a single resulting value

#ifndef ACCUMULATE_HPP
#define ACCUMULATE_HPP

#include "typelistfront.hpp"
#include "typelistisempty.hpp"
#include "typelistpopfront.hpp"

template<typename List, template<typename X, typename Y> class F, typename I, bool Empty = IsEmpty<List>::value>
class AccumulateT;

// recursive case:
template<typename List, template<typename X, typename Y> class F, typename I>
class AccumulateT<List, F, I, false> : public AccumulateT<PopFront<List>, F, typename F<I, Front<List>>::Type>
{
};

// basis case:
template<typename List, template<typename X, typename Y> class F, typename I>
class AccumulateT<List, F, I, true>
{
public:
    using Type = I;
};

template<typename List, template<typename X, typename Y> class F, typename I>
using Accumulate = typename AccumulateT<List, F, I>::Type;

#endif
