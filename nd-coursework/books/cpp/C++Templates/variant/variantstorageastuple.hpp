// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: variantstorageastuple.hpp
// Author: crdrisko
// Date: 12/12/2020-06:29:58
// Description: A simple, yet inefficient, storage mechanism for a Variant<> using a Tuple<>

#ifndef VARIANTSTORAGEASTUPLE_HPP
#define VARIANTSTORAGEASTUPLE_HPP

#include "../tuples/tuple.hpp"

template<typename... Types>
class Variant
{
public:
    Tuple<Types...> storage;
    unsigned char discriminator;
};

#endif
