// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: universalmem.cpp
// Author: crdrisko
// Date: 08/17/2021-08:37:41
// Description: Demonstrating how an rvalue reference to a member type of a template parameter is not a universal reference

#include <iostream>
#include <string>
#include <vector>

template<typename T>
void insert(T& coll, typename T::value_type&& arg)
{
    coll.push_back(arg);
}

int main()
{
    std::vector<std::string> coll;

    // ...

    insert(coll, std::string {"prvalue"});   // OK

    // ...

    std::string str {"lvalue"};
    // insert(coll, str);              // ERROR: T::value_type&& is not a universal reference
    insert(coll, std::move(str));   // OK

    // ...
}
