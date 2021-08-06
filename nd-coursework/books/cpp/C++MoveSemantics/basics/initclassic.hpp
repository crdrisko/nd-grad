// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: initclassic.hpp
// Author: crdrisko
// Date: 08/05/2021-07:59:15
// Description: A Person class initializing members the classical way

#ifndef INITCLASSIC_HPP
#define INITCLASSIC_HPP

#include <string>

class Person
{
private:
    std::string first;   // first name
    std::string last;    // last name

public:
    Person(const std::string& f, const std::string& l) : first {f}, last {l} {}

    // ...
};

#endif
