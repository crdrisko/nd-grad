// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: accum5.cpp
// Author: crdrisko
// Date: 08/18/2020-10:27:50
// Description: Using the accumulator with a new multiplication policy

#include <iostream>

#include "accum5.hpp"

class MultPolicy
{
public:
    template<typename T1, typename T2>
    static void accumulate(T1& total, T2 const& value)
    {
        total *= value;
    }
};

int main()
{
    // create array of 5 integer values
    int num[] = { 1, 2, 3, 4, 5 };

    // print product of all values
    std::cout << "the product of the integer values is "
              << accum<int, MultPolicy>(num, num + 5)
              << '\n';
}
