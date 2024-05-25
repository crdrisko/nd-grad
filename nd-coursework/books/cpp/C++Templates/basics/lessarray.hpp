// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: lessarray.hpp
// Author: cdrisko
// Date: 07/29/2020-20:44:25
// Description: Templates specifically designed for raw arrays or string literals

#ifndef LESSARRAY_HPP
#define LESSARRAY_HPP

template<typename T, int N, int M>
bool less(T (&a)[N], T (&b)[M])
{
    for (int i = 0; i < N && i < M; ++i)
    {
        if (a[i] < b[i])
            return true;
        if (b[i] < a[i])
            return false;
    }

    return N < M;
}

#endif
