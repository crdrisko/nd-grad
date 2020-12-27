// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: stackauto.cpp
// Author: cdrisko
// Date: 07/27/2020-07:54:22
// Description: Using the Stack<> template with the automatically deduced size type

#include <iostream>
#include <string>
#include <type_traits>

#include "stackauto.hpp"

int main()
{
    Stack<int, 20u>        int20Stack;                      // stack of up to 20 ints
    Stack<std::string, 40> stringStack;                     // stack of up to 40 strings

    // manipulate stack of up to 20 ints
    int20Stack.push(7);
    std::cout << int20Stack.top() << '\n';
    auto size1 = int20Stack.size();

    // manipulate stack of up to 40 strings
    stringStack.push("hello");
    std::cout << stringStack.top() << '\n';
    auto size2 = stringStack.size();

    if (!std::is_same_v<decltype(size1), decltype(size2)>)
        std::cout << "size types differ" << '\n';
}
