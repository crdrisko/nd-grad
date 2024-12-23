// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: hasmember.cpp
// Author: crdrisko
// Date: 08/31/2020-07:53:24
// Description: Using our DEFINE_HAS_MEMBER macro to test a few cases on different members

#include "hasmember.hpp"

#include <iostream>
#include <utility>
#include <vector>

DEFINE_HAS_MEMBER(size);
DEFINE_HAS_MEMBER(first);

int main()
{
    std::cout << "int::size: " << HasMemberT_size<int>::value << '\n';
    std::cout << "std::vector<int>::size: " << HasMemberT_size<std::vector<int>>::value << '\n';
    std::cout << "std::pair<int, int>::first: " << HasMemberT_first<std::pair<int, int>>::value << '\n';
}
