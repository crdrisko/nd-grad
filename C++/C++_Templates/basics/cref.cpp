// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
//
// Name: cref.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/12/2020-12:41:17
// Description: Using std::cref() to pass a parameter to a function "as if by reference"

#include <functional>
#include <iostream>
#include <string>

void printString(std::string const& s)
{
    std::cout << s << '\n';
}

template<typename T>
void printT(T arg)
{
    printString(arg);                                       // might convert arg back to std::string
}

int main()
{
    std::string s = "hello";
    printT(s);                                              // print s passed by value
    printT(std::cref(s));                                   // print s passed "as if by reference"
}
