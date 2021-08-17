// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: universalspec.cpp
// Author: crdrisko
// Date: 08/17/2021-09:16:11
// Description: An example of rvalue references of parameters in full specialization

#include <iostream>
#include <string>
#include <vector>

// primary template taking a universal reference:
template<typename Coll, typename T>
void insert(Coll& coll, T&& arg)
{
    std::cout << "primary template for type T called\n";
    coll.push_back(arg);
}

// full specialization for rvalues of type std::string:
template<>
void insert(std::vector<std::string>& coll, std::string&& arg)
{
    std::cout << "full specialization for type std::string&& called\n";
    coll.push_back(arg);
}

// full specialization for lvalues of type std::string:
template<>
void insert(std::vector<std::string>& coll, const std::string& arg)
{
    std::cout << "full specialization for type const std::string& called\n";
    coll.push_back(arg);
}

int main()
{
    std::vector<std::string> coll;

    // ...

    insert(coll, std::string {"prvalue"});   // calls full specialization for rvalues

    std::string str {"lvalue"};
    insert(coll, str);              // calls full specialization for lvalues
    insert(coll, std::move(str));   // calls full specialization for rvalues

    // ...
}
