// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: elementtype.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/18/2020-12:00:34
// Description: Using the type function, ElementT, to print type information

#include <iostream>
#include <typeinfo>
#include <vector>

#include "elementtype.hpp"

template<typename T>
void printElementType(T const& c)
{
    std::cout << "Container of "
              << typeid(typename ElementT<T>::Type).name()
              << " elements.\n";
}

int main()
{
    std::vector<bool> s;
    printElementType(s);
    int arr[42];
    printElementType(arr);
}
