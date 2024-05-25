// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: stacknontype.cpp
// Author: cdrisko
// Date: 07/26/2020-17:40:39
// Description: Demonstrating the use of the Stack<> template with the non-type parameter

#include "stacknontype.hpp"

#include <iostream>
#include <string>

int main()
{
    Stack<int, 20> int20Stack;            // stack of up to 20 ints
    Stack<int, 40> int40Stack;            // stack of up to 40 ints
    Stack<std::string, 40> stringStack;   // stack of up to 40 strings

    // manipulate stack of up to 20 ints
    int20Stack.push(7);
    std::cout << int20Stack.top() << '\n';
    int20Stack.pop();

    // manipulate stack of up to 40 strings
    stringStack.push("hello");
    std::cout << stringStack.top() << '\n';
    stringStack.pop();
}
