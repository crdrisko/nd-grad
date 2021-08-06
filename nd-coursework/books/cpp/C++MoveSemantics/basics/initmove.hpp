// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: initmove.hpp
// Author: crdrisko
// Date: 08/05/2021-08:01:11
// Description: A Person class initializing members via moved parameters passed by value

#ifndef INITMOVE_HPP
#define INITMOVE_HPP

#include <string>

class Person
{
private:
    std::string first;   // first name
    std::string last;    // last name

public:
    Person(std::string f, std::string l) : first {std::move(f)}, last {std::move(l)} {}

    // ...
};

#endif
