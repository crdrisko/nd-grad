// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: boolstring.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/30/2020-21:48:25
// Description: An example of specializing member function templates

#ifndef BOOLSTRING_HPP
#define BOOLSTRING_HPP

#include <string>

class BoolString
{
private:
    std::string value;

public:
    BoolString(std::string const& s) : value{s} {}

    template<typename T = std::string>
    T get() const { return value; }                         // get value (converted to T)
};

#endif
