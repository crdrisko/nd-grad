// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: errornovel2.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/12/2020-15:12:34
// Description: A simple example with another large error message

#include <string>
#include <unordered_set>

class Customer
{
private:
    std::string name;

public:
    Customer(std::string const& n) : name(n) {}

    std::string getName() const { return name; }
};

int main()
{
    // provide our own hash function
    struct MyCustomerHash
    {
        // NOTE: missing const is only an error with g++ and clang:
        std::size_t operator()(Customer const& c)
        {
            return std::hash<std::string>()(c.getName());
        }
    };

    // and use it for a hash table of Customers
    std::unordered_set<Customer, MyCustomerHash> coll;

    // ...
}
