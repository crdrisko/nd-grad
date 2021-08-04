// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: customer1.cpp
// Author: crdrisko
// Date: 08/03/2021-10:22:33
// Description: An example of implicit move semantics in ordinary classes

#include <iostream>
#include <random>
#include <utility>   // for std::move()

#include "customer.hpp"

int main()
{
    // create a customer with some initial values:
    Customer c {"Wolfgang Amadeus Mozart"};
    for (int val : {0, 8, 15})
        c.addValue(val);

    std::cout << "c: " << c << '\n';   // print value of initialized c

    // insert the customer twice into a collection of customers:
    std::vector<Customer> customers;
    customers.push_back(c);              // copy into the vector
    customers.push_back(std::move(c));   // move into the vector
    std::cout << "c: " << c << '\n';     // print the value of moved-from c

    // print all customers in the collection:
    std::cout << "customers:\n";
    for (const Customer& cust : customers)
        std::cout << " " << cust << '\n';
}
