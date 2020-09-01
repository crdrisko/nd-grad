// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: rparam1.cpp - Version 1.0.0
// Author: crdrisko
// Date: 09/01/2020-10:05:27
// Description: Using a function that allows parameter passing by value or by reference

#include "rparam.hpp"
#include "rparamcls.hpp"

template<typename T1, typename T2>
void foo(typename RParam<T1>::Type p1, typename RParam<T2>::Type p2)
{
    // ...
}

int main()
{
    MyClass1 mc1;
    MyClass2 mc2;
    foo<MyClass1, MyClass2>(mc1, mc2);
}
