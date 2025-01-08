// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: stack3test.cpp
// Author: crdrisko
// Date: 07/26/2020-14:54:33
// Description: Using the class template Stack<> with varrying element and container types

#include "stack3.hpp"

#include <deque>
#include <iostream>

int main()
{
    // stack of ints
    Stack<int> intStack;

    // stack of doubles using a std::deque<> to manage the elements
    Stack<double, std::deque<double>> dblStack;

    // manipulate int stack
    intStack.push(7);
    std::cout << intStack.top() << '\n';
    intStack.pop();

    // manipulate double stack
    dblStack.push(42.42);
    std::cout << dblStack.top() << '\n';
    dblStack.pop();
}
