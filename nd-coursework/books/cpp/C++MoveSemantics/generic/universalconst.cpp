// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: universalconst.cpp
// Author: crdrisko
// Date: 08/17/2021-08:28:32
// Description: Using universal references to forward constness

#include <iostream>
#include <string>

void iterate(std::string::iterator beg, std::string::iterator end)
{
    std::cout << "do some non-const stuff with the passed range\n";
}

void iterate(std::string::const_iterator beg, std::string::const_iterator end)
{
    std::cout << "do some const stuff with the passed range\n";
}

template<typename T>
void process(T&& coll)
{
    iterate(coll.begin(), coll.end());
}

int main()
{
    std::string v {"v"};
    const std::string c {"c"};

    process(v);                   // coll binds to a non-const lvalue, iterators passed
    process(c);                   // coll binds to a const lvalue, const_iterators passed
    process(std::string {"t"});   // coll binds to a non-const prvalue, iterators passed
    process(std::move(v));        // coll binds to a non-const xvalue, iterators passed
    process(std::move(c));        // coll binds to a const xvalue, const_iterators passed
}
