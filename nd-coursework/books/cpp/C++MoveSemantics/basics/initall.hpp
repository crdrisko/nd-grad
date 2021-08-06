// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: initall.hpp
// Author: crdrisko
// Date: 08/05/2021-07:54:07
// Description: A Person class initializing members via Rvalue references

#ifndef INITALL_HPP
#define INITALL_HPP

#include <string>

class Person
{
private:
    std::string first;   // first name
    std::string last;    // last name

public:
    Person(const std::string& f, const std::string& l) : first {f}, last {l} {}

    Person(const std::string& f, std::string&& l) : first {f}, last {std::move(l)} {}

    Person(std::string&& f, const std::string& l) : first {std::move(f)}, last {l} {}

    Person(std::string&& f, std::string&& l) : first {std::move(f)}, last {std::move(l)} {}

    Person(const char* f, const char* l) : first {f}, last {l} {}

    Person(const char* f, const std::string& l) : first {f}, last {l} {}

    Person(const char* f, std::string&& l) : first {f}, last {std::move(l)} {}

    Person(const std::string& f, const char* l) : first {f}, last {l} {}

    Person(std::string&& f, const char* l) : first {std::move(f)}, last {l} {}

    // ...
};

#endif
