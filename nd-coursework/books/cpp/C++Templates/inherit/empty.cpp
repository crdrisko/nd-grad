// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: empty.cpp
// Author: cdrisko
// Date: 07/28/2020-19:58:45
// Description: Demonstrating that even an empty class still has a nonzero size

#include <iostream>

class EmptyClass
{
};

int main() { std::cout << "sizeof(EmptyClass): " << sizeof(EmptyClass) << '\n'; }
