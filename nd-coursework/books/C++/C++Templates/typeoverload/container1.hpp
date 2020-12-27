// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: container1.hpp
// Author: crdrisko
// Date: 09/04/2020-07:21:40
// Description: Embedding EnableIf<> in a default template argument rather than in the return type

#ifndef CONTAINER1_HPP
#define CONTAINER1_HPP

#include <iterator>

#include "enableif.hpp"
#include "isconvertible.hpp"

template<typename Iterator>
constexpr bool IsInputIterator =
    IsConvertible<
        typename std::iterator_traits<Iterator>::iterator_category,
        std::input_iterator_tag>;

template<typename T>
class Container
{
public:
    // construct from an input iterator sequence:
    template<typename Iterator,
             typename = EnableIf<IsInputIterator<Iterator>>>
    Container(Iterator first, Iterator last);

    // convert to a container so long as the value types are convertible:
    template<typename U, typename = EnableIf<IsConvertible<T, U>>>
    operator Container<U>() const;
};

#endif
