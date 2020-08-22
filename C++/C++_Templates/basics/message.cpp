// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: message.cpp - Version 1.0.0
// Author: cdrisko
// Date: 07/27/2020-07:54:49
// Description: Passing statically locally declared strings as constant arrays (C++17 and on)

#include <iostream>

template<auto T>                                           // take value of any possible nontype parameter (since C++17)
class Message
{
public:
    void print() { std::cout << T << '\n'; }
};

int main()
{
    Message<42> msg1;
    msg1.print();                                           // initialize with int 42 and print that value

    static char const s[] = "hello";
    Message<s> msg2;                                        // initialize with char const[6] "hello"
    msg2.print();                                           // and print that value
}
