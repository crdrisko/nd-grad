// Name: errornovel1.cpp - Version 1.0.0
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
