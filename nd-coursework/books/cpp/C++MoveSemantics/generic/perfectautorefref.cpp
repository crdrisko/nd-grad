// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: perfectautorefref.cpp
// Author: crdrisko
// Date: 08/17/2021-09:55:05
// Description: Passing a return value later but still keeping its type and value category with auto&&

#include <iostream>
#include <string>

void process(const std::string&) { std::cout << "process(const std::string&)\n"; }
void process(std::string&) { std::cout << "process(std::string&)\n"; }
void process(std::string&&) { std::cout << "process(std::string&&)\n"; }

const std::string& computeConstLRef(const std::string& str) { return str; }
std::string& computeLRef(std::string& str) { return str; }
std::string&& computeRRef(std::string&& str) { return std::move(str); }
std::string computeValue(const std::string& str) { return str; }

int main()
{
    auto&& r1 = computeConstLRef("tmp");
    process(std::forward<decltype(r1)>(r1));   // calls process(const std::string&)

    std::string str {"lvalue"};
    auto&& r2 = computeLRef(str);
    process(std::forward<decltype(r2)>(r2));   // calls process(std::string&)

    auto&& r3 = computeRRef("tmp");
    process(std::forward<decltype(r3)>(r3));   // calls process(std::string&&)

    auto&& r4 = computeRRef(std::move(str));
    process(std::forward<decltype(r4)>(r4));   // calls process(std::string&&)

    auto&& r5 {computeValue("tmp")};
    process(std::forward<decltype(r5)>(r5));   // calls process(std::string&&)
}
