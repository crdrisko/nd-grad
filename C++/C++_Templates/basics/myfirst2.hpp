// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
//
// Name: myfirst2.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/12/2020-14:56:26
// Description: A re-worked version of printTypeof<> where declaration and definition are in the header file

#ifndef MYFIRST2_HPP
#define MYFIRST2_HPP

#include <iostream>
#include <typeinfo>

// declaration of template
template<typename T>
void printTypeof(T const&);

// implementation/definition of template
template<typename T>
void printTypeof(T const& x)
{
    std::cout << typeid(x).name() << '\n';
}

#endif
