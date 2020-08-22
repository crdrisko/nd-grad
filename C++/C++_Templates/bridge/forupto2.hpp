// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: forupto2.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/27/2020-13:09:13
// Description: Limiting an increase in code size by using a function pointer instead of a function template

#ifndef FORUPTO2_HPP
#define FORUPTO2_HPP

void forUpTo(int n, void (*f)(int))
{
    for (int i = 0; i != n; ++i)
        f(i);                                               // call passed function f for i
}

#endif
