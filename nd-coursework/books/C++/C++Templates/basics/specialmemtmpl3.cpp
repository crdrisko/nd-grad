// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: specialmemtmpl3.cpp
// Author: cdrisko
// Date: 08/01/2020-08:45:59
// Description: Using the final version of our Person class with perfect forwarding and enable_if

#include <string>
#include <utility>

#include "specialmemtmpl3.hpp"

int main()
{
    std::string s = "sname";
    Person p1(s);                                           // init with string object => calls TMPL-CONSTR
    Person p2("tmp");                                       // init with string literal => calls TMPL-CONSTR
    Person p3(p1);                                          // OK => calls COPY-CONSTR
    Person p4(std::move(p1));                               // OK => calls MOVE-CONSTR
}
