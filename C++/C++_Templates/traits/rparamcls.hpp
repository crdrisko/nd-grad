// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: rparamcls.hpp - Version 1.0.0
// Author: crdrisko
// Date: 09/01/2020-10:05:17
// Description: Two classes which specify how they should be called as read-only arguments

#ifndef RPARAMCLS_HPP
#define RPARAMCLS_HPP

#include <iostream>

#include "rparam.hpp"

class MyClass1
{
public:
    MyClass1() {}
    MyClass1(MyClass1 const&) { std::cout << "MyClass1 copy constructor called\n"; }
};

class MyClass2
{
public:
    MyClass2() {}
    MyClass2(MyClass2 const&) { std::cout << "MyClass2 copy constructor called\n"; }
};

// pass MyClass2 objects with RParam<> by value
template<>
class RParam<MyClass2>
{
public:
    using Type = MyClass2;
};

#endif
