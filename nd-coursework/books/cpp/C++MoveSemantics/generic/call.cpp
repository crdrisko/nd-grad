// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: call.cpp
// Author: crdrisko
// Date: 08/17/2021-09:42:18
// Description: Showing how the use of decltype(auto) allows us to call both functions that return by value and functions that return by reference

#include "call.hpp"

#include <iostream>
#include <string>

std::string nextString() { return "Let's dance"; }

std::ostream& print(std::ostream& strm, const std::string& val) { return strm << "value: " << val; }

std::string&& returnArg(std::string&& arg) { return std::move(arg); }

int main()
{
    auto s = call(nextString);   // call() returns temporary object

    auto&& ref = call(returnArg, std::move(s));   // call() returns rvalue reference to s
    std::cout << " s:   " << s << '\n';
    std::cout << " ref: " << ref << '\n';

    auto str = std::move(ref);   // move value from s and ref to str
    std::cout << " s:   " << s << '\n';
    std::cout << " ref: " << ref << '\n';
    std::cout << " str: " << str << '\n';

    call(print, std::cout, str) << '\n';   // call() returns reference to std::cout
}
