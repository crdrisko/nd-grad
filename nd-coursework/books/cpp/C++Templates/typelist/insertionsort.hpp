// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: insertionsort.hpp
// Author: crdrisko
// Date: 10/01/2020-17:56:18
// Description: The shell of the insertion sort algorithm acting on a typelist

#ifndef INSERTIONSORT_HPP
#define INSERTIONSORT_HPP

#include "consfront.hpp"
#include "consisempty.hpp"
#include "conspopfront.hpp"
#include "insertsorted.hpp"
#include "typelistfront.hpp"
#include "typelistisempty.hpp"
#include "typelistpopfront.hpp"

template<typename List, template<typename T, typename U> class Compare, bool = IsEmpty<List>::value>
class InsertionSortT;

template<typename List, template<typename T, typename U> class Compare>
using InsertionSort = typename InsertionSortT<List, Compare>::Type;

// recursive case (insert first element into sorted list):
template<typename List, template<typename T, typename U> class Compare>
class InsertionSortT<List, Compare, false>
    : public InsertSortedT<InsertionSort<PopFront<List>, Compare>, Front<List>, Compare>
{
};

// basis case (an empty list is sorted):
template<typename List, template<typename T, typename U> class Compare>
class InsertionSortT<List, Compare, true>
{
public:
    using Type = List;
};

#endif
