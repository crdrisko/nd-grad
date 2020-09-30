// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: myfirst.cpp
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
