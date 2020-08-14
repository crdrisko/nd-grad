// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
//
// Name: myfirst.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/12/2020-14:49:53
// Description: Implementation/definition of printTypeof<> template

#include <iostream>
#include <typeinfo>

#include "myfirst.hpp"

template<typename T>
void printTypeof(T const& x)
{
    std::cout << typeid(x).name() << '\n';
}
