// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: consfront.hpp
// Author: crdrisko
// Date: 10/02/2020-08:35:46
// Description: A metafunction for extracting the first element from a cons-style typelist

#ifndef CONSFRONT_HPP
#define CONSFRONT_HPP

template<typename List>
class FrontT
{
public:
    using Type = typename List::Head;
};

template<typename List>
using Front = typename FrontT<List>::Type;

#endif
