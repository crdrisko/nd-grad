// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: nthelement.hpp
// Author: crdrisko
// Date: 09/10/2020-12:16:40
// Description: A metafunction for finding the element at a given index of a typelist

#ifndef NTHELEMENT_HPP
#define NTHELEMENT_HPP

#include "typelistfront.hpp"
#include "typelistpopfront.hpp"

// recursive case:
template<typename List, unsigned N>
class NthElementT : public NthElementT<PopFront<List>, N - 1>
{
};

// basis case:
template<typename List>
class NthElementT<List, 0> : public FrontT<List>
{
};

template<typename List, unsigned N>
using NthElement = typename NthElementT<List, N>::Type;

#endif
