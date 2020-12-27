// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: findindexof.hpp
// Author: crdrisko
// Date: 12/12/2020-06:55:31
// Description: A metafunction that returns the index of a specific type in a list

#ifndef FINDINDEXOF_HPP
#define FINDINDEXOF_HPP

#include <type_traits>

#include "../traits/ifthenelse.hpp"
#include "../typelist/typelistfront.hpp"
#include "../typelist/typelistisempty.hpp"
#include "../typelist/typelistpopfront.hpp"

template<typename List, typename T, unsigned N = 0, bool Empty = IsEmpty<List>::value>
struct FindIndexOfT;

// recursive case:
template<typename List, typename T, unsigned N>
struct FindIndexOfT<List, T, N, false> : public IfThenElse<std::is_same<Front<List>, T>::value,
                                                           std::integral_constant<unsigned, N>,
                                                           FindIndexOfT<PopFront<List>, T, N + 1>>
{
};

// base case:
template<typename List, typename T, unsigned N>
struct FindIndexOfT<List, T, N, true>
{
};

#endif
