// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isfundatest.cpp - Version 1.0.0
// Author: crdrisko
// Date: 09/01/2020-07:31:22
// Description: Testing if different types are fundamental types or not using our IsFundaT trait

#include <iostream>

#include "isfunda.hpp"

template<typename T>
void test(T const&)
{
    if (IsFundaT<T>::value)
        std::cout << "T is a fundamental type\n";
    else
        std::cout << "T is not a fundamental type\n";
}

int main()
{
    test(7);
    test("hello");
}
