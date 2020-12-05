// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: tuple0.hpp
// Author: crdrisko
// Date: 10/19/2020-09:50:10
// Description: A recursive formulation of tuple storage

#ifndef TUPLE0_HPP
#define TUPLE0_HPP

template<typename... Types>
class Tuple;

// recursive case:
template<typename Head, typename... Tail>
class Tuple<Head, Tail...>
{
private:
    Head head;
    Tuple<Tail...> tail;

public:
    // constructors:
    Tuple() {}
    Tuple(Head const& head, Tuple<Tail...> const& tail) : head(head), tail(tail) {}

    // ...

    Head& getHead() { return head; }
    Head const& getHead() const { return head; }
    Tuple<Tail...>& getTail() { return tail; }
    Tuple<Tail...> const& getTail() const { return tail; }
};

// basis case:
template<>
class Tuple<>
{
    // no storage required
};

#endif
