// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: printmax.cpp
// Author: crdrisko
// Date: 08/14/2020-13:12:03
// Description: Handling generic containers with iterators

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

#include "MyClass.hpp"

template<typename T>
void printMax(T const& coll)
{
    // compute position of maximum value
    auto pos = std::max_element(coll.begin(), coll.end());

    // print value of maximum element of coll (if any):
    if (pos != coll.end())
        std::cout << *pos << '\n';
    else
        std::cout << "empty" << '\n';
}

int main()
{
    std::vector<MyClass> c1;
    std::list<MyClass> c2;

    // ...

    printMax(c1);
    printMax(c2);
}
