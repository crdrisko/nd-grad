// Name: arrays.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/29/2020-20:51:00
// Description: All possible overloads for arrays

#ifndef ARRAYS_HPP
#define ARRAYS_HPP

#include <iostream>

template<typename T>
struct MyClass;                                             // primary template

template<typename T, std::size_t SZ>
struct MyClass<T[SZ]>                                       // partial specialization for arrays of known bounds
{
    static void print() { std::cout << "print() for T[" << SZ << "]\n"; }
};

template<typename T, std::size_t SZ>
struct MyClass<T(&)[SZ]>                                    // partial specialization for references to arrays of known bounds
{
    static void print() { std::cout << "print() for T(&)[" << SZ << "]\n"; }
};

template<typename T>
struct MyClass<T[]>                                         // partial specialization for arrays of unknown bounds
{
    static void print() { std::cout << "print() for T[]\n"; }
};

template<typename T>
struct MyClass<T(&)[]>                                      // partial specialization for references to arrays of unknown bounds
{
    static void print() { std::cout << "print() for T(&)[]\n"; }
};

template<typename T>
struct MyClass<T*>                                          // partial specialization for pointers
{
    static void print() { std::cout << "print() for T*\n"; }
};

#endif
