// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: addspace.hpp
// Author: cdrisko
// Date: 07/27/2020-11:05:55
// Description: Using a fold expression to print all arguments of a variadic template

#ifndef ADDSPACE_HPP
#define ADDSPACE_HPP

#include <iostream>

template<typename T>
class AddSpace
{
private:
    T const& ref;                                           // refer to argument passed in constructor

public:
    AddSpace(T const& r) : ref{r} {}
    friend std::ostream& operator<<(std::ostream& os, AddSpace<T> s)
    {
        return os << s.ref << ' ';                          // output passed argument and a space
    }
};

template<typename... Args>
void print(Args... args)
{
    ( std::cout << ... << AddSpace(args) ) << '\n';
}

#endif
