// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: move1.cpp
// Author: cdrisko
// Date: 07/31/2020-21:45:39
// Description: Creating perfect forwarding by 'hard-coding' each use case

#include <iostream>
#include <utility>

class X
{
    // ...
};

void g(X&)
{
    std::cout << "g() for variable\n";
}

void g(X const&)
{
    std::cout << "g() for constant\n";
}

void g(X&&)
{
    std::cout << "g() for movable object\n";
}

// let f() forward argument val to g():
void f(X& val)
{
    g(val);                                                 // val is non-const lvalue => calls g(X&)
}

void f(X const& val)
{
    g(val);                                                 // val is const lvalue => calls g(X const&)
}

void f(X&& val)
{
    g(std::move(val));                                      // val is non-const lvalue => needs std::move to call g(X&&)
}

int main()
{
    X v;                                                    // create variable
    X const c;                                              // create constant

    f(v);                                                   // f() for non-constant object calls f(X&) => calls g(X&)
    f(c);                                                   // f() for constant object calls f(X const&) => calls g(X const&)
    f(X());                                                 // f() for temporary calls f(X&&) => calls g(X&&)
    f(std::move(v));                                        // f() for movable variable calls f(X&&) => calls g(X&&)
}
