// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: personmove.hpp
// Author: crdrisko
// Date: 08/11/2021-09:19:59
// Description: Creating the same Person class as before but guaranteeing our move constructor will not throw

#ifndef PERSONMOVE_HPP
#define PERSONMOVE_HPP

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

    Person(Person&& p) noexcept : name {std::move(p.name)}   // guarantee not to throw
    {
        std::cout << "MOVE " << name << '\n';
    }

    // ...
};

#endif
