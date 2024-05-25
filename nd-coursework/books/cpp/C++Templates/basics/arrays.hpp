// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: arrays.hpp
// Author: cdrisko
// Date: 07/29/2020-20:51:00
// Description: All possible overloads for arrays

#ifndef ARRAYS_HPP
#define ARRAYS_HPP

#include <iostream>

template<typename T>
struct MyClass;   // primary template

template<typename T, std::size_t SZ>
struct MyClass<T[SZ]>   // partial specialization for arrays of known bounds
{
    static void print() { std::cout << "print() for T[" << SZ << "]\n"; }
};

template<typename T, std::size_t SZ>
struct MyClass<T (&)[SZ]>   // partial specialization for references to arrays of known bounds
{
    static void print() { std::cout << "print() for T(&)[" << SZ << "]\n"; }
};

template<typename T>
struct MyClass<T[]>   // partial specialization for arrays of unknown bounds
{
    static void print() { std::cout << "print() for T[]\n"; }
};

template<typename T>
struct MyClass<T (&)[]>   // partial specialization for references to arrays of unknown bounds
{
    static void print() { std::cout << "print() for T(&)[]\n"; }
};

template<typename T>
struct MyClass<T*>   // partial specialization for pointers
{
    static void print() { std::cout << "print() for T*\n"; }
};

#endif
