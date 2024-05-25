// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: move2.cpp
// Author: cdrisko
// Date: 07/31/2020-21:59:35
// Description: Creating perfect forwarding by using std::forward<>

#include <iostream>
#include <utility>

class X
{
    // ...
};

void g(X&) { std::cout << "g() for variable\n"; }

void g(X const&) { std::cout << "g() for constant\n"; }

void g(X&&) { std::cout << "g() for movable object\n"; }

// let f() perfect forward argument val to g():
template<typename T>
void f(T&& val)
{
    g(std::forward<T>(val));   // call the right g() for any passed argument val
}

int main()
{
    X v;         // create variable
    X const c;   // create constant

    f(v);              // f() for non-constant object calls f(X&) => calls g(X&)
    f(c);              // f() for constant object calls f(X const&) => calls g(X const&)
    f(X());            // f() for temporary calls f(X&&) => calls g(X&&)
    f(std::move(v));   // f() for movable variable calls f(X&&) => calls g(X&&)
}
