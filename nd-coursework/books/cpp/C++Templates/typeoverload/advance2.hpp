// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: advance2.hpp
// Author: crdrisko
// Date: 09/04/2020-07:33:09
// Description: Advancing iterators using C++17's constexpr if instead of multiple specializations

#ifndef ADVANCE2_HPP
#define ADVANCE2_HPP

#include <iterator>

template<typename Iterator>
constexpr bool IsRandomAccessIterator
    = IsConvertible<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>;

template<typename Iterator>
constexpr bool IsBidirectionalIterator
    = IsConvertible<typename std::iterator_traits<Iterator>::iterator_category, std::bidirectional_iterator_tag>;

template<typename Iterator, typename Distance>
void advanceIter(Iterator& x, Distance n)
{
    if constexpr (IsRandomAccessIterator<Iterator>)
    {
        // implementation for random access iterators:
        x += n;   // constant time
    }
    else if constexpr (IsBidirectionalIterator<Iterator>)
    {
        // implementation for bidirectional iterators
        if (n > 0)
            for (; n > 0; ++x, --n)
            {
            }   // linear time for positive n
        else
            for (; n < 0; --x, ++n)
            {
            }   // linear time for negative n
    }
    else
    {
        // implementation for all other iterators that are at least input iterators:
        if (n < 0)
            throw "advanceIter(): invalid iterator category for negative n";

        while (n > 0)   // linear time for positive only
        {
            ++x;
            --n;
        }
    }
}

#endif
