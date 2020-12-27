// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: tuplestorage3.hpp
// Author: crdrisko
// Date: 12/05/2020-07:54:55
// Description: Using the EBCO on the head element to improve (once again) the storage of our tuple, this time guarenteing uniqueness

#ifndef TUPLESTORAGE3_HPP
#define TUPLESTORAGE3_HPP

#include "tupleelt1.hpp"

template<typename... Types>
class Tuple;

// recursive case:
template<typename Head, typename... Tail>
class Tuple<Head, Tail...> : private TupleElt<sizeof...(Tail), Head>, private Tuple<Tail...>
{
    using HeadElt = TupleElt<sizeof...(Tail), Head>;

public:
    Head& getHead() { return static_cast<HeadElt*>(this)->get(); }
    Head const& getHead() const { return static_cast<HeadElt*>(this)->get(); }
    Tuple<Tail...>& getTail() { return *this; }
    Tuple<Tail...> const& getTail() const { return *this; }
};

// basic case:
template<>
class Tuple<>
{
    // no storage required
};

#endif
