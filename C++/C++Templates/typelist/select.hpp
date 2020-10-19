// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: select.hpp
// Author: crdrisko
// Date: 10/02/2020-08:34:13
// Description: Using pack expansions to select the elements in a given list of indicies producing a new Typelist

#ifndef SELECT_HPP
#define SELECT_HPP

#include "nthelement.hpp"
#include "typelist.hpp"
#include "valuelist.hpp"

template<typename Types, typename Indicies>
class SelectT;

template<typename Types, unsigned... Indicies>
class SelectT<Types, Valuelist<unsigned, Indicies...>>
{
    using Type = Typelist<NthElement<Types, Indicies>...>;
};

template<typename Types, typename Indicies>
using Select = typename SelectT<Types, Indicies>::Type;

#endif
