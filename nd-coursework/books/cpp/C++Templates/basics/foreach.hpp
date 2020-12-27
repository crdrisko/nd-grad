// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: foreach.hpp
// Author: crdrisko
// Date: 08/13/2020-10:54:48
// Description: A simple implentation of the standard library's for_each() algorithm

#ifndef FOREACH_HPP
#define FOREACH_HPP

template<typename Iter, typename Callable>
void foreach(Iter current, Iter end, Callable op)
{
    while (current != end)                                  // as long as not reached the end
    {
        op(*current);                                       // call passed operator for current element
        ++current;                                          // and move iterator to next element
    }
}

#endif
