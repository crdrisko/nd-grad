// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: universalconstructor.cpp
// Author: crdrisko
// Date: 08/09/2021-15:12:20
// Description: The reason you should be very careful when implementing a constructor that has one single universal reference parameter

#include <iostream>

class X
{
public:
    X() = default;

    X(const X&) { std::cout << "copy constructor\n"; }

    X(X&&) { std::cout << "move constructor\n"; }

    template<typename U>
    X(U&&)
    {
        std::cout << "universal constructor\n";
    }
};

int main()
{
    X xv;
    const X xc;

    X xcc {xc};              // OK: calls copy constructor
    X xvc {xv};              // OOPS: calls universal constructor
    X xvm {std::move(xv)};   // OK: calls move constructor
    X xcm {std::move(xc)};   // OOPS: calls universal constructor
}
