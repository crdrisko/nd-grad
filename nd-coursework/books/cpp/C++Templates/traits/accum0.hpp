// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: accum0.hpp
// Author: crdrisko
// Date: 08/18/2020-11:25:15
// Description: Extending the interface of our accumulator to utilize the functionality of iterator traits

#ifndef ACCUM0_HPP
#define ACCUM0_HPP

#include <iterator>

template<typename Iter>
auto accum(Iter start, Iter end)
{
    using VT = typename std::iterator_traits<Iter>::value_type;

    VT total {};   // assume this actually creates a zero value

    while (start != end)
    {
        total += *end;
        ++start;
    }

    return total;
}

#endif
