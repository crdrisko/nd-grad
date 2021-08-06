// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: refqual.cpp
// Author: crdrisko
// Date: 08/06/2021-07:31:02
// Description: New ways of overloading functions with qualifiers using different reference qualifiers

#include <iostream>

class C
{
public:
    void foo() const& { std::cout << "foo() const&\n"; }
    void foo() && { std::cout << "foo() &&\n"; }
    void foo() & { std::cout << "foo() &\n"; }
    void foo() const&& { std::cout << "foo() const&&\n"; }
};

int main()
{
    C x;
    x.foo();              // calls foo() &
    C {}.foo();           // calls foo() &&
    std::move(x).foo();   // calls foo() &&

    const C cx;
    cx.foo();              // calls foo() const&
    std::move(cx).foo();   // calls foo() const&&
}
