// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: specialmemtmpl2.hpp
// Author: crdrisko
// Date: 08/01/2020-08:45:53
// Description: Replacing the overloading constructors by using a generic constructor with perfect forwarding

#ifndef SPECIALMEMTMPL2_HPP
#define SPECIALMEMTMPL2_HPP

#include <iostream>
#include <string>
#include <utility>

class Person
{
private:
    std::string name;

public:
    // generic constructor for passed initial name:
    template<typename STR>
    explicit Person(STR&& n) : name(std::forward<STR>(n))
    {
        std::cout << "TMPL-CONSTR for '" << name << "'\n";
    }

    // copy and move constructor:
    Person(Person const& p) : name(p.name) { std::cout << "COPY-CONSTR Person '" << name << "'\n"; }

    Person(Person&& p) : name(std::move(p.name)) { std::cout << "MOVE-CONSTR Person '" << name << "'\n"; }
};

#endif
