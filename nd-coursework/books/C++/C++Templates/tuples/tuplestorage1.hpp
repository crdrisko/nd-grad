// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: tuplestorage1.hpp
// Author: crdrisko
// Date: 12/05/2020-07:31:58
// Description: Applying the EBCO to help optimize recursive storage of a tuple

#ifndef TUPLESTORAGE1_HPP
#define TUPLESTORAGE1_HPP

#include "tuple.hpp"

// recursive case:
template<typename Head, typename... Tail>
class Tuple<Head, Tail...> : private Tuple<Tail...>
{
private:
    Head head;

public:
    Head& getHead() { return head; }
    Head const& getHead() const { return head; }
    Tuple<Tail...>& getTail() { return *this; }
    Tuple<Tail...> const& getTail() const { return *this; }
};

#endif
