// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: specialmemtmpl1.cpp - Version 1.0.0
// Author: cdrisko
// Date: 08/01/2020-08:45:50
// Description: Supporting move semantics by providing overloading a constructor

#include <iostream>
#include <string>
#include <utility>

class Person
{
private:
    std::string name;

public:
    // constructor for passed initial name:
    explicit Person(std::string const& n) : name(n)
    {
        std::cout << "copying string-CONSTR for '" << name << "'\n";
    }

    explicit Person(std::string&& n) : name(std::move(n))
    {
        std::cout << "moving string-CONSTR for '" << name << "'\n";
    }

    // copy and move constructor:
    Person(Person const& p) : name(p.name)
    {
        std::cout << "COPY-CONSTR Person '" << name << "'\n";
    }

    Person(Person&& p) : name(std::move(p.name))
    {
        std::cout << "MOVE-CONSTR Person '" << name << "'\n";
    }
};

int main()
{
    std::string s = "sname";
    Person p1(s);                                           // init with string object => calls copying string-CONSTR
    Person p2("tmp");                                       // init with string literal => calls moving string-CONSTR
    Person p3(p1);                                          // copy Person => calls COPY-CONSTR
    Person p4(std::move(p1));                               // move Person => calls MOVE-CONSTR
}
