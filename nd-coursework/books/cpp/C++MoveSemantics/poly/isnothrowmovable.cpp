// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: isnothrowmovable.cpp
// Author: crdrisko
// Date: 08/09/2021-15:18:16
// Description: Demonstrating the different behavior of the standard and the user-defined type trait

#include "isnothrowmovable.hpp"

#include <iostream>
#include <string>

class Base
{
    std::string id;

    // ...

public:
    virtual void print() const = 0;

    // ...

    virtual ~Base() = default;

protected:
    // protected copy and move semantics (also forces abstract base class):
    Base(const Base&) = default;
    Base(Base&&)      = default;

    // disable assignment operator (due to the problem of slicing):
    Base& operator=(Base&&) = delete;
    Base& operator=(const Base&) = delete;
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << "std::is_nothrow_move_constructible_v<Base>: " << std::is_nothrow_move_constructible_v<Base> << '\n';
    std::cout << "std::is_nothrow_movable_v<Base>:            " << is_nothrow_movable_v<Base> << '\n';
}
