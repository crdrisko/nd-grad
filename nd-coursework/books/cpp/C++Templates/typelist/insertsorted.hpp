// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: insertsorted.hpp
// Author: crdrisko
// Date: 10/01/2020-18:00:20
// Description: A metafunction that inserts a value into an already-sorted list at the first point that will keep the list sorted

#ifndef INSERTSORTED_HPP
#define INSERTSORTED_HPP

#include "consisempty.hpp"
#include "consfront.hpp"
#include "conspopfront.hpp"
#include "conspushfront.hpp"
#include "identity.hpp"
#include "typelistisempty.hpp"
#include "typelistfront.hpp"
#include "typelistpopfront.hpp"
#include "typelistpushfront.hpp"
#include "../traits/ifthenelse.hpp"

template<typename List, typename Element,
         template<typename T, typename U> class Compare,
         bool = IsEmpty<List>::value>
class InsertSortedT;

// recursive case:
template<typename List, typename Element,
         template<typename T, typename U> class Compare>
class InsertSortedT<List, Element, Compare, false>
{
    // compute the tail of the resulting list:
    using NewTail = typename IfThenElse<Compare<Element, Front<List>>::value,
                                        IdentityT<List>,
                                        InsertSortedT<PopFront<List>, Element, Compare>
                                       >::Type;

    // compute the head of the resulting list:
    using NewHead = IfThenElse<Compare<Element, Front<List>>::value,
                                       Element,
                                       Front<List>>;

public:
    using Type = PushFront<NewTail, NewHead>;
};

// basis case:
template<typename List, typename Element,
         template<typename T, typename U> class Compare>
class InsertSortedT<List, Element, Compare, true>
    : public PushFrontT<List, Element> {};

template<typename List, typename Element,
         template<typename T, typename U> class Compare>
using InsertSorted = typename InsertSortedT<List, Element, Compare>::Type;

#endif
