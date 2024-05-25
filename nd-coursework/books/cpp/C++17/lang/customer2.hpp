// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: customer2.hpp
// Author: crdrisko
// Date: 09/28/2020-08:42:42
// Description: Providing a Customer class that provides an API to read and modify its members

#ifndef CUSTOMER2_HPP
#define CUSTOMER2_HPP

#include <string>
#include <utility>   // for std::move()

class Customer
{
private:
    std::string first;
    std::string last;
    long val;

public:
    Customer(std::string f, std::string l, long v) : first {std::move(f)}, last {std::move(l)}, val {v} {}

    const std::string& firstname() const { return first; }
    std::string& firstname() { return first; }

    const std::string& lastname() const { return last; }
    std::string& lastname() { return last; }

    const long& value() const { return val; }
    long& value() { return val; }
};

#endif
