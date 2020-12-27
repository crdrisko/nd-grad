// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: tuplestorage2.hpp
// Author: crdrisko
// Date: 12/05/2020-07:42:06
// Description: Using the EBCO on the head element to improve (once again) the storage of our tuple

#ifndef TUPLESTORAGE2_HPP
#define TUPLESTORAGE2_HPP

#include <utility>

template<typename... Types>
class Tuple;

template<typename T>
class TupleElt
{
    T value;

public:
    TupleElt() = default;

    template<typename U>
    TupleElt(U&& other) : value(std::forward<U>(other))
    {
    }

    T& get() { return value; }
    T const& get() const { return value; }
};

// recursive case:
template<typename Head, typename... Tail>
class Tuple<Head, Tail...> : private TupleElt<Head>, private Tuple<Tail...>
{
public:
    Head& getHead()
    {
        // potentially ambiguous
        return static_cast<TupleElt<Head>*>(this)->get();
    }

    Head const& getHead() const
    {
        // potentially ambiguous
        return static_cast<TupleElt<Head>*>(this)->get();
    }

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
