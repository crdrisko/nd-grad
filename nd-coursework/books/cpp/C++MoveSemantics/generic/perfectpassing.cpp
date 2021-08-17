// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: perfectpassing.cpp
// Author: crdrisko
// Date: 08/17/2021-09:54:56
// Description: Passing a return value to another function directly while keeping its type and value category

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
    process(computeConstLRef("tmp"));   // calls process(const std::string&)

    std::string str {"lvalue"};
    process(computeLRef(str));   // calls process(std::string&)

    process(computeRRef("tmp"));   // calls process(std::string&&)

    process(computeRRef(std::move(str)));   // calls process(std::string&&)

    process(computeValue("tmp"));   // calls process(std::string&&)
}
