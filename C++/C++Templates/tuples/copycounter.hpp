// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: copycounter.hpp
// Author: crdrisko
// Date: 11/07/2020-08:53:11
// Description: A class which copies the number of times it is copied

#ifndef COPYCOUNTER_HPP
#define COPYCOUNTER_HPP

template<int N>
struct CopyCounter
{
    inline static unsigned numCopies = 0;
    CopyCounter() {}
    CopyCounter(CopyCounter const&) { ++numCopies; }
};

#endif
