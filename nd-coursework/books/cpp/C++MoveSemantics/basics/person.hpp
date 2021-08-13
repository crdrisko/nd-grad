// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: person.hpp
// Author: crdrisko
// Date: 08/11/2021-09:09:03
// Description: A class which introduces a type with a string member and implements a copy and a move constructor to make calls of these constructors visible

#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>
#include <string>

class Person
{
private:
    std::string name;

public:
    Person(const char* n) : name {n} {}

    std::string getName() const { return name; }

    // print out when we copy or move:
    Person(const Person& p) : name {p.name} { std::cout << "COPY " << name << '\n'; }

    Person(Person&& p) : name {std::move(p.name)} { std::cout << "MOVE " << name << '\n'; }

    // ...
};

#endif
