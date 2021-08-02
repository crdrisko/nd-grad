// Copyright (c) 2007 Johan Thelin. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing1_03.cpp
// Author: crdrisko
// Date: 08/02/2021-07:54:21
// Description: Dynamic memory without Qt

#include <iostream>

#include "Listing1_02.hpp"

int main(int argc, char** argv)
{
    MyClass* a = new MyClass("foo");
    MyClass* b = new MyClass("ba-a-ar");
    MyClass* c = new MyClass("baz");

    std::cout << a->text() << " (" << a->getLengthOfText() << ")" << std::endl;
    a->setText(b->text());
    std::cout << a->text() << " (" << a->getLengthOfText() << ")" << std::endl;

    int result = a->getLengthOfText() - c->getLengthOfText();

    delete a;
    delete b;
    delete c;

    return result;
}
