// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: sizeof.cpp
// Author: crdrisko
// Date: 08/18/2020-11:44:17
// Description: Using the sizeof function to return a usable type for template parameters

#include <cstddef>
#include <iostream>

template<typename T>
struct TypeSize
{
    static std::size_t const value = sizeof(T);
};

int main()
{
    std::cout << "TypeSize<int>::value = "
              << TypeSize<int>::value << '\n';
}
