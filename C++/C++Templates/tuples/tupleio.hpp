// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: tupleio.hpp
// Author: crdrisko
// Date: 10/20/2020-07:29:04
// Description: Overloading the operator<<() to print any tuple whose element type can be printed

#ifndef TUPLEIO_HPP
#define TUPLEIO_HPP

#include <iostream>

#include "tuple.hpp"

void printTuple(std::ostream& strm, Tuple<> const&, bool isFirst = true)
{
    strm << (isFirst ? '(' : ')');
}

template<typename Head, typename... Tail>
void printTuple(std::ostream& strm, Tuple<Head, Tail...> const& t, bool isFirst = true)
{
    strm << (isFirst ? "(" : ", ");
    strm << t.getHead();
    printTuple(strm, t.getTail(), false);
}

template<typename... Types>
std::ostream& operator<<(std::ostream& strm, Tuple<Types...> const& t)
{
    printTuple(strm, t);
    return strm;
}

#endif
