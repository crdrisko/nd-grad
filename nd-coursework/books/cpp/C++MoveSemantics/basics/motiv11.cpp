// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: motiv.cpp
// Author: crdrisko
// Date: 08/03/2021-07:16:12
// Description: Motivation for move semantics with an example since C++11 (using move semantics)

#include <string>
#include <vector>

std::vector<std::string> createAndInsert()
{
    std::vector<std::string> coll;   // create vector of strings
    coll.reserve(3);                 // reserve memory for 3 elements
    std::string s = "data";          // create string object

    coll.push_back(s);              // insert string object
    coll.push_back(s + s);          // insert temporary string
    coll.push_back(std::move(s));   // insert string (we no longer need the value of s)

    return coll;   // return vector of strings
}

int main()
{
    std::vector<std::string> v;   // create empty vector of strings

    // ...

    v = createAndInsert();   // assign returned vector of strings

    // ...
}
