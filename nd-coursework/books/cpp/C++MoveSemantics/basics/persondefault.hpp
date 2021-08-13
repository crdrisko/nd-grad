// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: persondefault.hpp
// Author: crdrisko
// Date: 08/12/2021-10:32:06
// Description: Creating a Person class where the compiler will add the noexcept guarantee automatically

#ifndef PERSONDEFAULT_HPP
#define PERSONDEFAULT_HPP

#include <iostream>
#include <string>

class Person
{
private:
    std::string name;

public:
    Person(const char* n) : name {n} {}

    std::string getName() const { return name; }

    // print out when we copy:
    Person(const Person& p) : name {p.name} { std::cout << "COPY " << name << '\n'; }

    // force default generated move constructor:
    Person(Person&& p) = default;

    // ...
};

#endif
