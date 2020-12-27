// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: variantstorageasunion.hpp
// Author: crdrisko
// Date: 12/12/2020-06:32:46
// Description: Overlapping the storage of each of the possible types by recursively unwrapping the variant using a union

#ifndef VARIANTSTORAGEASUNION_HPP
#define VARIANTSTORAGEASUNION_HPP

template<typename... Types>
union VariantStorage;

template<typename Head, typename... Tail>
union VariantStorage<Head, Tail...>
{
    Head head;
    VariantStorage<Tail...> tail;
};

template<>
union VariantStorage<>
{
};

#endif
