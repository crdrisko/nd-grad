// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: transform.hpp
// Author: crdrisko
// Date: 09/30/2020-07:24:53
// Description: A metafunction that takes a metafunction and applies it to each element of a typelist

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "typelistfront.hpp"
#include "typelistisempty.hpp"
#include "typelistpopfront.hpp"
#include "typelistpushfront.hpp"

template<typename List, template<typename T> class MetaFun, bool Empty = IsEmpty<List>::value>
class TransformT;

// recursive case:
template<typename List, template<typename T> class MetaFun>
class TransformT<List, MetaFun, false>
    : public PushFrontT<typename TransformT<PopFront<List>, MetaFun>::Type, typename MetaFun<Front<List>>::Type>
{
};

// basis case:
template<typename List, template<typename T> class MetaFun>
class TransformT<List, MetaFun, true>
{
public:
    using Type = List;
};

template<typename List, template<typename T> class MetaFun>
using Transform = typename TransformT<List, MetaFun>::Type;

#endif
