// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: lessstring.hpp
// Author: cdrisko
// Date: 07/29/2020-20:44:32
// Description: A function template designed for string literals (and other char arrays)

#ifndef LESSSTRING_HPP
#define LESSSTRING_HPP

template<int N, int M>
bool less(char const(&a)[N], char const(&b)[M])
{
    for (int i = 0; i < N && i < M; ++i)
    {
        if (a[i] < b[i]) return true;
        if (b[i] < a[i]) return false;
    }

    return N < M;
}

#endif
