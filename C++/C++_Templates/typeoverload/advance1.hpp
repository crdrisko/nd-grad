// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: advance1.hpp - Version 1.0.0
// Author: crdrisko
// Date: 09/03/2020-08:10:04
// Description: A first attempt at providing multiple specializations when advancing a specific integer type

#ifndef ADVANCE1_HPP
#define ADVANCE1_HPP

#include <iterator>

#include "enableif.hpp"
#include "isconvertible.hpp"

template<typename Iterator>
constexpr bool IsRandomAccessIterator =
    IsConvertible<
        typename std::iterator_traits<Iterator>::iterator_category,
        std::random_access_iterator_tag>;

// implementation for random access iterators:
template<typename Iterator, typename Distance>
EnableIf<IsRandomAccessIterator<Iterator>>
advanceIter(Iterator& x, Distance n)
{
    x += n;                                                 // constant time
}


template<typename Iterator>
constexpr bool IsBidirectionalIterator =
    IsConvertible<
        typename std::iterator_traits<Iterator>::iterator_category,
        std::bidirectional_iterator_tag>;

// implementation for bidirectional iterators:
template<typename Iterator, typename Distance>
EnableIf<IsBidirectionalIterator<Iterator> &&
         !IsRandomAccessIterator<Iterator>>
advanceIter(Iterator& x, Distance n)
{
    if (n > 0)
        for ( ; n > 0; ++x, --n) {}                         // linear time
    else
        for ( ; n < 0; --x, ++n) {}                         // linear time
}


// implementation for all other iterators:
template<typename Iterator, typename Distance>
EnableIf<!IsBidirectionalIterator<Iterator>>
advanceIter(Iterator& x, Distance n)
{
    if (n < 0)
        throw "advanceIter(): invalid iterator category for negative n";

    while (n > 0)                                           // linear time
    {
        ++x;
        --n;
    }
}

#endif
