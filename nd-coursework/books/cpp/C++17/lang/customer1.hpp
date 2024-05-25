// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: customer1.hpp
// Author: crdrisko
// Date: 09/28/2020-08:14:47
// Description: How to enable structured bindings for a type Customer

#ifndef CUSTOMER1_HPP
#define CUSTOMER1_HPP

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

    std::string getFirst() const { return first; }
    std::string getLast() const { return last; }
    long getValue() const { return val; }
};

#endif
