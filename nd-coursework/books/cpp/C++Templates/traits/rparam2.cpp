// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: rparam2.cpp
// Author: crdrisko
// Date: 09/01/2020-10:05:30
// Description: Improvements in using a function that allows parameter passing by value or by reference

#include <utility>

#include "rparam.hpp"
#include "rparamcls.hpp"

// function that allows parameter passing by value or by reference
template<typename T1, typename T2>
void foo_core(typename RParam<T1>::Type p1, typename RParam<T2>::Type p2)
{
    // ...
}

// wrapper to avoid explicit template parameter passing
template<typename T1, typename T2>
void foo(T1&& p1, T2&& p2)
{
    foo_core<T1, T2>(std::forward<T1>(p1), std::forward<T2>(p2));
}

int main()
{
    MyClass1 mc1;
    MyClass2 mc2;
    foo(mc1, mc2);   // same as foo_core<MyClass1, MyClass2>(mc1, mc2)
}
