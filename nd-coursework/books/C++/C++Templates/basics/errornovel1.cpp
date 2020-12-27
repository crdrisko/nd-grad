// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: errornovel1.cpp
// Author: crdrisko
// Date: 08/12/2020-15:12:31
// Description: A simple example with a large error message

#include <algorithm>
#include <map>
#include <string>

int main()
{
    std::map<std::string, double> coll;

    // ...

    // find the first nonempty string in coll:
    auto pos = std::find_if(coll.begin(), coll.end(),
                            [](std::string const& s) { return s != ""; });
}
