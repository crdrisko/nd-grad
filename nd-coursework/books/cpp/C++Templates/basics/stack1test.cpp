// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: stack1test.cpp
// Author: crdrisko
// Date: 07/26/2020-14:09:48
// Description: Using the class template Stack<> (prior to C++17)

#include "stack1.hpp"

#include <iostream>
#include <string>

int main()
{
    Stack<int> intStack;              // stack of ints
    Stack<std::string> stringStack;   // stack of strings

    // manipulate int stack
    intStack.push(7);
    std::cout << intStack.top() << '\n';

    // manipulate string stack
    stringStack.push("hello");
    std::cout << stringStack.top() << '\n';
    stringStack.pop();
}
