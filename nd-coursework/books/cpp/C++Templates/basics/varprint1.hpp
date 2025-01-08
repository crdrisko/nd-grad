// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: varprint1.hpp
// Author: crdrisko
// Date: 07/27/2020-10:21:12
// Description: Printing a variable number of arguments

#ifndef VARPRINT1_HPP
#define VARPRINT1_HPP

#include <iostream>

void print() {}

template<typename T, typename... Types>
void print(T firstArg, Types... args)
{
    std::cout << firstArg << '\n';   // print first argument
    print(args...);                  // call print() for remaining arguments
}

#endif
