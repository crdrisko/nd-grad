// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: intstring.hpp
// Author: crdrisko
// Date: 08/08/2021-07:23:02
// Description: A class containing two different representations of a value, an integral and string value

#ifndef INTSTRING_HPP
#define INTSTRING_HPP

#include <iostream>
#include <string>

class IntString
{
private:
    int val;            // value
    std::string sval;   // cached string representation of the value

public:
    IntString(int i = 0) : val {i}, sval {std::to_string(i)} {}

    void setValue(int i)
    {
        val  = i;
        sval = std::to_string(i);
    }

    // ...

    void dump() const { std::cout << " [" << val << "/'" << sval << "']\n"; }
};

#endif
