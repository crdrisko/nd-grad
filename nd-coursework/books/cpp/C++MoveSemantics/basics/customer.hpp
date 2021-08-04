// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: customer.hpp
// Author: crdrisko
// Date: 08/03/2021-10:07:00
// Description: A simple class with members of types where move semantics can make a difference

#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class Customer
{
private:
    std::string name;          // name of the customer
    std::vector<int> values;   // some values of the customer

public:
    Customer(const std::string& n) : name {n} { assert(!name.empty()); }

    std::string getName() const { return name; }
    void addValue(int val) { values.push_back(val); }

    friend std::ostream& operator<<(std::ostream& strm, const Customer& cust)
    {
        strm << '[' << cust.name << ": ";
        for (int val : cust.values)
            strm << val << ' ';
        strm << ']';

        return strm;
    }
};

#endif
