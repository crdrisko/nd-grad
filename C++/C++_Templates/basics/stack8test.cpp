// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: stack8test.cpp - Version 1.0.0
// Author: cdrisko
// Date: 07/31/2020-07:42:09
// Description: Using all features of the final implementation of the Stack class template

#include <iostream>
#include <vector>

#include "stack8.hpp"

int main()
{
    Stack<int>   iStack;                                    // stack of ints
    Stack<float> fStack;                                    // stack of floats

    // manipulate int stack
    iStack.push(1);
    iStack.push(2);
    std::cout << "iStack.top(): " << iStack.top() << '\n';

    // manipulate float stack
    fStack.push(3.3);
    std::cout << "fStack.top(): " << fStack.top() << '\n';

    // assign stack of different type and manipulate again
    fStack = iStack;
    fStack.push(4.4);
    std::cout << "fStack.top(): " << fStack.top() << '\n';

    // stack for doubles using a vector as an internal container
    Stack<double, std::vector> vStack;
    vStack.push(5.5);
    vStack.push(6.6);
    std::cout << "vStack.top(): " << vStack.top() << '\n';

    vStack = fStack;
    std::cout << "vStack: ";

    while ( !vStack.empty() )
    {
        std::cout << vStack.top() << ' ';
        vStack.pop();
    }

    std::cout << '\n';
}
