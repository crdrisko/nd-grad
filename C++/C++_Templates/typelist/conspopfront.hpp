// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: conspopfront.hpp
// Author: crdrisko
// Date: 10/02/2020-08:35:46
// Description: A metafunction removing the first element from a cons-style typelist

#ifndef CONSPOPFRONT_HPP
#define CONSPOPFRONT_HPP

template<typename List>
class PopFrontT
{
public:
    using Type = typename List::Tail;
};

template<typename List>
using PopFront = typename PopFrontT<List>::Type;

#endif
