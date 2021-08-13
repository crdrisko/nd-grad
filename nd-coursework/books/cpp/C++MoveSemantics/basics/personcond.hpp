// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: personcond.hpp
// Author: crdrisko
// Date: 08/12/2021-09:57:32
// Description: Using the noexcept keyword to specify a conditional guarantee not to throw

#ifndef PERSONCOND_HPP
#define PERSONCOND_HPP

#include <iostream>
#include <string>

class Person
{
private:
    std::string name;

public:
    Person(const char* n) : name {n} {}

    std::string getName() const { return name; }

    // Print out when we copy or move:
    Person(const Person& p) : name {p.name} { std::cout << "COPY " << name << '\n'; }

    Person(Person&& p) noexcept(std::is_nothrow_move_constructible<std::string>::value&& noexcept(std::cout << name))
        : name {std::move(p.name)}
    {
        std::cout << "MOVE " << name << '\n';
    }

    // ...
};

#endif
