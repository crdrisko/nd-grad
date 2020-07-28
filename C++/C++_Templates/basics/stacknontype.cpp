// Name: stacknontype.cpp - Version 1.0.0
// Author: cdrisko
// Date: 07/26/2020-17:40:39
// Description: Demonstrating the use of the Stack<> template with the non-type parameter

#include <iostream>
#include <string>

#include "stacknontype.hpp"

int main()
{
    Stack<int, 20>         int20Stack;                      // stack of up to 20 ints
    Stack<int, 40>         int40Stack;                      // stack of up to 40 ints
    Stack<std::string, 40> stringStack;                     // stack of up to 40 strings

    // manipulate stack of up to 20 ints
    int20Stack.push(7);
    std::cout << int20Stack.top() << '\n';
    int20Stack.pop();

    // manipulate stack of up to 40 strings
    stringStack.push("hello");
    std::cout << stringStack.top() << '\n';
    stringStack.pop();
}
