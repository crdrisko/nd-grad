// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: universalclass.cpp
// Author: crdrisko
// Date: 08/17/2021-09:16:06
// Description: An example of rvalue references of parameters in class templates

#include <iostream>
#include <string>
#include <vector>

template<typename T>
class Coll
{
private:
    std::vector<T> values;

public:
    Coll() = default;

    // function in class template:
    void insert(T&& val) { values.push_back(val); }
};

int main()
{
    Coll<std::string> coll;

    // ...

    coll.insert(std::string {"prvalue"});   // OK

    std::string str {"lvalue"};
    // coll.insert(str);              // ERROR: T&& of Coll<T> is not a universal reference
    coll.insert(std::move(str));   // OK

    // ...
}
