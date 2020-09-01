// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: passbyvalue.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/18/2020-13:36:04
// Description: Showing how a function template "decays" parameter types

#include <iostream>
#include <typeinfo>
#include <type_traits>

template<typename T>
void f(T) {}

template<typename A>
void printParameterType(void (*)(A))
{
    std::cout << "Parameter type: " << typeid(A).name() << '\n';
    std::cout << "- is int:     " << std::is_same<A, int>::value << '\n';
    std::cout << "- is const:   " << std::is_const<A>::value << '\n';
    std::cout << "- is pointer: " << std::is_pointer<A>::value << '\n';
}

int main()
{
    printParameterType(&f<int>);
    printParameterType(&f<int const>);
    printParameterType(&f<int[7]>);
    printParameterType(&f<int(int)>);
}
