// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: virtual.cpp
// Author: cdrisko
// Date: 07/29/2020-10:10:55
// Description: Demonstrating the use of parameterized virtuality with Mixins

#include <iostream>

class NotVirtual
{
};

class Virtual
{
public:
    virtual void foo() {}
};

template<typename... Mixins>
class Base : public Mixins...
{
public:
    // the virtuality of foo() depends on its declaration
    // (if any) in the base classes Mixins...
    void foo() { std::cout << "Base::foo()" << '\n'; }
};

template<typename... Mixins>
class Derived : public Base<Mixins...>
{
public:
    void foo() { std::cout << "Derived::foo()" << '\n'; }
};

int main()
{
    Base<NotVirtual>* p1 = new Derived<NotVirtual>;
    p1->foo();   // calls Base::foo()

    Base<Virtual>* p2 = new Derived<Virtual>;
    p2->foo();   // calls Derived::foo()

    delete p1;
    p1 = nullptr;

    delete p2;
    p2 = nullptr;
}
