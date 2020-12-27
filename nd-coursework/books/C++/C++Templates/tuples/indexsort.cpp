// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: indexsort.cpp
// Author: crdrisko
// Date: 11/22/2020-07:15:53
// Description: A demonstration of how the tuplesort algorithm would work

#include <algorithm>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> strings = {"banana", "apple", "cherry"};
    std::vector<unsigned> indices    = {0, 1, 2};

    std::sort(indices.begin(), indices.end(), [&strings](unsigned i, unsigned j) { return strings[i] < strings[j]; });
}
