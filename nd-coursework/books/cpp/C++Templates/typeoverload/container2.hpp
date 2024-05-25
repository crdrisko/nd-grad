// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: container2.hpp
// Author: crdrisko
// Date: 09/04/2020-07:47:27
// Description: Using C++20's concepts to describe the requirements of the template

#ifndef CONTAINER2_HPP
#define CONTAINER2_HPP

#include <iterator>

#include "isconvertible.hpp"

template<typename Iterator>
constexpr bool IsInputIterator
    = IsConvertible<typename std::iterator_traits<Iterator>::iterator_category, std::input_iterator_tag>;

template<typename Iterator>
constexpr bool IsRandomAccessIterator
    = IsConvertible<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>;

template<typename T>
class Container
{
public:
    // construct from an input iterator sequence:
    template<typename Iterator>
        requires IsInputIterator<Iterator>
    Container(Iterator first, Iterator last);

    // construct from a random access iterator sequence:
    template<typename Iterator>
        requires IsRandomAccessIterator<Iterator>
    Container(Iterator first, Iterator last);

    // convert to a container so long as the value types are convertible:
    template<typename U>
        requires IsConvertible<T, U>
    operator Container<U>() const;
};

#endif
