// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: members.cpp
// Author: crdrisko
// Date: 08/11/2021-09:25:08
// Description: Perfectly forwarding members of objects

#include <iostream>
#include <string>
#include <utility>
#include <vector>

template<typename Coll, typename T>
void insertBoth(Coll& coll, T&& p)
{
    // if p has move semantics, move a value but copy reference/static members
    coll.push_back(std::forward<T>(p).first);
    coll.push_back(std::forward<T>(p).second);
}

int main()
{
    std::string s {"outside"};
    std::pair<std::string, std::string> p1 {"p1first", "p1second"};
    std::pair<std::string, std::string&> p2 {"p2first", s};   // note: reference member

    std::vector<std::string> coll;

    insertBoth(coll, p1);   // does copy both members
    std::cout << "p1.first:  " << p1.first << '\n';
    std::cout << "p1.second: " << p1.second << '\n';

    insertBoth(coll, std::move(p1));   // does move both members
    std::cout << "p1.first:  " << p1.first << '\n';
    std::cout << "p1.second: " << p1.second << '\n';

    insertBoth(coll, std::move(p2));   // does move value and copy reference member
    std::cout << "p2.first:  " << p2.first << '\n';
    std::cout << "p2.second: " << p2.second << '\n';

    std::cout << "coll:\n";
    for (const auto& elem : coll)
        std::cout << "- elem: " << elem << '\n';
}
