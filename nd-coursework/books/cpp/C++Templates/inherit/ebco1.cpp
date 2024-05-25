// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: ebco1.cpp
// Author: cdrisko
// Date: 07/28/2020-20:03:44
// Description: Clarifying what the the empty base class optimization (EBCO) means in practice

#include <iostream>

class Empty
{
    using Int = int;   // type alias members don't make a class nonempty
};

class EmptyToo : public Empty
{
};

class EmptyThree : public EmptyToo
{
};

int main()
{
    std::cout << "sizeof(Empty):      " << sizeof(Empty) << '\n';
    std::cout << "sizeof(EmptyToo):   " << sizeof(EmptyToo) << '\n';
    std::cout << "sizeof(EmptyThree): " << sizeof(EmptyThree) << '\n';
}
