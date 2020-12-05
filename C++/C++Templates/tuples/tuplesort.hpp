// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: tuplesort.hpp
// Author: crdrisko
// Date: 11/22/2020-06:54:02
// Description: Using the select() function and InsertionSort algorithm to sort a tuple

#ifndef TUPLESORT_HPP
#define TUPLESORT_HPP

#include "../typelist/ctvalue.hpp"
#include "../typelist/insertionsort.hpp"
#include "../typelist/nthelement.hpp"
#include "makeindexlist.hpp"
#include "select.hpp"
#include "tuple.hpp"

// metafunction wrapper that compares the elements in a tuple:
template<typename List, template<typename T, typename U> class F>
class MetafunOfNthElementT
{
public:
    template<typename T, typename U>
    class Apply;

    template<typename N, typename M>
    class Apply<CTValue<unsigned, M>, CTValue<unsigned, N>> : public F<NthElement<List, M>, NthElement<List, N>>
    {
    };
};

// sort a tuple based on comparing the element types:
template<template<typename T, typename U> class Compare, typename... Elements>
auto sort(Tuple<Elements...> const& t)
{
    return select(t,
        InsertionSort<MakeIndexList<sizeof...(Elements)>,
            MetafunOfNthElementT<Tuple<Elements...>, Compare>::template Apply>());
}

#endif
