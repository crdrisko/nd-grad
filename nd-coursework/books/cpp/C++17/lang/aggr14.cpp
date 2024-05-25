// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: aggr14.cpp
// Author: crdrisko
// Date: 09/29/2020-18:00:47
// Description: An incompatibility when using aggregates in C++17 compared to previous versions

struct Derived;

struct Base
{
    friend struct Derived;

private:
    Base() {}
};

struct Derived : Base
{
};

int main()
{
    Derived d1 {};   // ERROR since C++17
    Derived d2;      // still OK (but might not initialize)
}
