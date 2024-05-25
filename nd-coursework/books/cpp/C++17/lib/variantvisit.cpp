// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: variantvisit.cpp
// Author: crdrisko
// Date: 11/08/2020-14:11:23
// Description: Using function objects as visitors for std::variant<>'s

#include <iostream>
#include <string>
#include <variant>

struct MyVisitor
{
    void operator()(int i) const { std::cout << "int:    " << i << '\n'; }
    void operator()(std::string s) const { std::cout << "string: " << s << '\n'; }
    void operator()(long double d) const { std::cout << "double: " << d << '\n'; }
};

int main()
{
    std::variant<int, std::string, double> var(42);
    std::visit(MyVisitor(), var);   // calls operator() for int
    var = "hello";
    std::visit(MyVisitor(), var);   // calls operator() for string
    var = 42.7;
    std::visit(MyVisitor(), var);   // calls operator() for long double
}
